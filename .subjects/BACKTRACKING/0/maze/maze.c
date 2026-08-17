#include <unistd.h>
#include <stdlib.h>

static int g_size;
static int **g_maze;
static int **g_sol;

static void print_solution(void)
{
    int i;
    int j;

    i = 0;
    while (i < g_size)
    {
        j = 0;
        while (j < g_size)
        {
            if (g_sol[i][j] == 2)
                write(1, "S", 1);
            else if (g_sol[i][j] == 3)
                write(1, "E", 1);
            else if (g_sol[i][j] == 1)
                write(1, "X", 1);
            else
                write(1, ".", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

static int solve(int x, int y)
{
    if (x == g_size - 1 && y == g_size - 1 && g_maze[x][y] == 1)
    {
        g_sol[x][y] = 3;
        return (1);
    }
    if (x >= 0 && x < g_size && y >= 0 && y < g_size
        && g_maze[x][y] == 1 && g_sol[x][y] == 0)
    {
        g_sol[x][y] = 1;
        if (solve(x + 1, y))
            return (1);
        if (solve(x, y + 1))
            return (1);
        if (solve(x - 1, y))
            return (1);
        if (solve(x, y - 1))
            return (1);
        g_sol[x][y] = 0;
    }
    return (0);
}

static void free_maze(void)
{
    int i;

    i = 0;
    while (i < g_size)
    {
        free(g_maze[i]);
        free(g_sol[i]);
        i++;
    }
    free(g_maze);
    free(g_sol);
}

int main(void)
{
    char buf[1];
    int i;
    int j;

    g_size = 0;
    while (read(0, buf, 1) == 1 && buf[0] != '\n')
        g_size++;
    if (g_size == 0)
        return (1);
    lseek(0, 0, SEEK_SET);
    g_maze = (int **)malloc(sizeof(int *) * g_size);
    g_sol = (int **)malloc(sizeof(int *) * g_size);
    i = 0;
    while (i < g_size)
    {
        g_maze[i] = (int *)malloc(sizeof(int) * g_size);
        g_sol[i] = (int *)malloc(sizeof(int) * g_size);
        j = 0;
        while (j < g_size)
        {
            read(0, buf, 1);
            if (buf[0] == '1' || buf[0] == '0')
            {
                g_maze[i][j] = buf[0] - '0';
                g_sol[i][j] = 0;
                j++;
            }
        }
        read(0, buf, 1);
        i++;
    }
    g_sol[0][0] = 2;
    if (solve(0, 0))
        print_solution();
    free_maze();
    return (0);
}
