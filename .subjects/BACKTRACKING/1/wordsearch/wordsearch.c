#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static char **g_grid;
static char *g_word;
static int g_rows;
static int g_cols;
static int g_found;

static void print_pos(int sr, int sc, int er, int ec)
{
    char buf[32];
    int len;

    buf[0] = '(';
    len = 1;
    if (sr >= 10) { buf[len++] = '0' + sr / 10; buf[len++] = '0' + sr % 10; }
    else { buf[len++] = '0' + sr; }
    buf[len++] = ',';
    if (sc >= 10) { buf[len++] = '0' + sc / 10; buf[len++] = '0' + sc % 10; }
    else { buf[len++] = '0' + sc; }
    buf[len++] = ')';
    buf[len++] = '-';
    buf[len++] = '(';
    if (er >= 10) { buf[len++] = '0' + er / 10; buf[len++] = '0' + er % 10; }
    else { buf[len++] = '0' + er; }
    buf[len++] = ',';
    if (ec >= 10) { buf[len++] = '0' + ec / 10; buf[len++] = '0' + ec % 10; }
    else { buf[len++] = '0' + ec; }
    buf[len++] = ')';
    buf[len++] = '\n';
    write(1, buf, len);
}

static int is_safe(int r, int c, int idx, int **visited)
{
    if (r < 0 || r >= g_rows || c < 0 || c >= g_cols)
        return (0);
    if (visited[r][c])
        return (0);
    if (g_grid[r][c] != g_word[idx])
        return (0);
    return (1);
}

static void search(int r, int c, int idx, int **visited, int sr, int sc)
{
    int dr[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dc[] = {1, -1, 0, 0, 1, -1, 1, -1};
    int i;

    if (g_found)
        return;
    if (g_word[idx] == '\0')
    {
        print_pos(sr, sc, r, c);
        g_found = 1;
        return;
    }
    i = 0;
    while (i < 8)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (is_safe(nr, nc, idx, visited))
        {
            visited[nr][nc] = 1;
            search(nr, nc, idx + 1, visited, sr, sc);
            visited[nr][nc] = 0;
        }
        i++;
    }
}

static void free_grid(void)
{
    int i;

    i = 0;
    while (i < g_rows)
    {
        free(g_grid[i]);
        i++;
    }
    free(g_grid);
}

int main(void)
{
    char buf[1024];
    int len;
    int r;
    int c;
    int **visited;

    len = 0;
    while (read(0, &buf[len], 1) == 1 && buf[len] != '\n')
        len++;
    buf[len] = '\0';
    g_word = strdup(buf);
    len = 0;
    while (read(0, &buf[len], 1) == 1 && buf[len] != '\n')
        len++;
    buf[len] = '\0';
    g_rows = atoi(buf);
    len = 0;
    while (read(0, &buf[len], 1) == 1 && buf[len] != '\n')
        len++;
    buf[len] = '\0';
    g_cols = atoi(buf);
    g_grid = (char **)malloc(sizeof(char *) * g_rows);
    r = 0;
    while (r < g_rows)
    {
        g_grid[r] = (char *)malloc(sizeof(char) * (g_cols + 1));
        c = 0;
        while (c < g_cols)
        {
            read(0, &buf[0], 1);
            if (buf[0] != '\n')
            {
                g_grid[r][c] = buf[0];
                c++;
            }
        }
        g_grid[r][c] = '\0';
        r++;
    }
    visited = (int **)malloc(sizeof(int *) * g_rows);
    r = 0;
    while (r < g_rows)
    {
        visited[r] = (int *)calloc(g_cols, sizeof(int));
        r++;
    }
    g_found = 0;
    r = 0;
    while (r < g_rows && !g_found)
    {
        c = 0;
        while (c < g_cols && !g_found)
        {
            if (g_grid[r][c] == g_word[0])
            {
                visited[r][c] = 1;
                search(r, c, 1, visited, r, c);
                visited[r][c] = 0;
            }
            c++;
        }
        r++;
    }
    if (!g_found)
        write(1, "Word not found\n", 15);
    r = 0;
    while (r < g_rows)
    {
        free(visited[r]);
        r++;
    }
    free(visited);
    free(g_word);
    free_grid();
    return (0);
}
