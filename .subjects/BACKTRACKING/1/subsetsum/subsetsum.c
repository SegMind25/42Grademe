#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int *g_nums;
static int g_count;
static int g_target;
static int *g_path;
static int g_path_len;

static void print_path(void)
{
    char buf[256];
    int i;
    int pos;
    int n;

    pos = 0;
    i = 0;
    while (i < g_path_len)
    {
        n = g_path[i];
        if (n >= 10)
            buf[pos++] = '0' + n / 10;
        buf[pos++] = '0' + n % 10;
        if (i < g_path_len - 1)
            buf[pos++] = ' ';
        i++;
    }
    buf[pos++] = '\n';
    write(1, buf, pos);
}

static void solve(int idx, int remaining)
{
    if (remaining == 0)
    {
        print_path();
        return;
    }
    if (idx >= g_count || remaining < 0)
        return;
    g_path[g_path_len] = g_nums[idx];
    g_path_len++;
    solve(idx + 1, remaining - g_nums[idx]);
    g_path_len--;
    solve(idx + 1, remaining);
}

int main(void)
{
    char buf[4096];
    int len;
    int i;
    int num;

    len = 0;
    while (read(0, &buf[len], 1) == 1 && buf[len] != '\n')
        len++;
    buf[len] = '\0';
    g_count = 0;
    i = 0;
    while (i < len)
    {
        while (i < len && buf[i] == ' ')
            i++;
        if (i < len)
        {
            num = 0;
            while (i < len && buf[i] >= '0' && buf[i] <= '9')
            {
                num = num * 10 + (buf[i] - '0');
                i++;
            }
            g_count++;
        }
    }
    g_nums = (int *)malloc(sizeof(int) * g_count);
    i = 0;
    len = 0;
    while (i < g_count)
    {
        while (len < (int)strlen(buf) && buf[len] == ' ')
            len++;
        num = 0;
        while (len < (int)strlen(buf) && buf[len] >= '0' && buf[len] <= '9')
        {
            num = num * 10 + (buf[len] - '0');
            len++;
        }
        g_nums[i] = num;
        i++;
    }
    len = 0;
    while (read(0, &buf[len], 1) == 1 && buf[len] != '\n')
        len++;
    buf[len] = '\0';
    g_target = atoi(buf);
    g_path = (int *)malloc(sizeof(int) * g_count);
    g_path_len = 0;
    solve(0, g_target);
    free(g_nums);
    free(g_path);
    return (0);
}
