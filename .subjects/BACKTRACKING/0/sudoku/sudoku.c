#include <unistd.h>
#include <stdlib.h>

static int board[9][9];

static int is_valid(int row, int col, int num)
{
    int i;

    i = 0;
    while (i < 9)
    {
        if (board[row][i] == num)
            return (0);
        if (board[i][col] == num)
            return (0);
        i++;
    }
    i = 0;
    while (i < 9)
    {
        int r = (row / 3) * 3 + i / 3;
        int c = (col / 3) * 3 + i % 3;
        if (board[r][c] == num)
            return (0);
        i++;
    }
    return (1);
}

static int solve(void)
{
    int row;
    int col;
    int num;

    row = 0;
    while (row < 9)
    {
        col = 0;
        while (col < 9)
        {
            if (board[row][col] == 0)
            {
                num = 1;
                while (num <= 9)
                {
                    if (is_valid(row, col, num))
                    {
                        board[row][col] = num;
                        if (solve())
                            return (1);
                        board[row][col] = 0;
                    }
                    num++;
                }
                return (0);
            }
            col++;
        }
        row++;
    }
    return (1);
}

static void print_board(void)
{
    int i;
    int j;

    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            char c = board[i][j] + '0';
            write(1, &c, 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}

int main(void)
{
    char buf[2];
    int i;
    int j;

    i = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            if (read(0, buf, 1) != 1)
                return (1);
            if (buf[0] >= '0' && buf[0] <= '9')
            {
                board[i][j] = buf[0] - '0';
                j++;
            }
            else if (buf[0] == '\n')
                continue;
            else
                return (1);
        }
        i++;
    }
    if (!solve())
        return (1);
    print_board();
    return (0);
}
