#include <stdlib.h>
#include <unistd.h>

static int g_size;

static void print_board(int *board)
{
    int i;
    int j;

    i = 0;
    while (i < g_size)
    {
        j = 0;
        while (j < g_size)
        {
            if (board[i] == j)
                write(1, "Q", 1);
            else
                write(1, ".", 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

static int is_safe(int *board, int row, int col)
{
    int i;

    i = 0;
    while (i < row)
    {
        if (board[i] == col)
            return (0);
        if (board[i] - i == col - row)
            return (0);
        if (board[i] + i == col + row)
            return (0);
        i++;
    }
    return (1);
}

static void solve(int *board, int row)
{
    int col;

    if (row == g_size)
    {
        print_board(board);
        write(1, "\n", 1);
        return;
    }
    col = 0;
    while (col < g_size)
    {
        if (is_safe(board, row, col))
        {
            board[row] = col;
            solve(board, row + 1);
        }
        col++;
    }
}

int main(int argc, char **argv)
{
    int *board;

    if (argc != 2)
        return (1);
    g_size = atoi(argv[1]);
    if (g_size <= 0)
        return (1);
    board = (int *)malloc(sizeof(int) * g_size);
    if (!board)
        return (1);
    solve(board, 0);
    free(board);
    return (0);
}
