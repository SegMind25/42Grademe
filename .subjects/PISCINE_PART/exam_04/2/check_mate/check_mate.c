#include <unistd.h>

/* reference: is the King (K) attacked by a Pawn, Bishop, Rook or Queen? */

static int	is_piece(char c)
{
	return (c == 'P' || c == 'B' || c == 'R' || c == 'Q' || c == 'K');
}

static char	at(char **board, int size, int y, int x)
{
	int	len;

	if (y < 0 || x < 0 || y >= size)
		return ('.');
	len = 0;
	while (board[y][len])
		len++;
	return (x < len ? board[y][x] : '.');
}

/* first piece met from the king in direction (dy, dx) */
static char	first_piece(char **board, int size, int ky, int kx, int dy, int dx)
{
	int	y;
	int	x;

	y = ky + dy;
	x = kx + dx;
	while (y >= 0 && x >= 0 && y < size && x < size)
	{
		if (is_piece(at(board, size, y, x)))
			return (at(board, size, y, x));
		y += dy;
		x += dx;
	}
	return ('.');
}

static int	in_check(char **board, int size, int ky, int kx)
{
	int	dy;
	int	dx;
	char	c;

	/* pawns capture diagonally towards the top of the board */
	if (at(board, size, ky + 1, kx - 1) == 'P' || at(board, size, ky + 1, kx + 1) == 'P')
		return (1);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dy || dx)
			{
				c = first_piece(board, size, ky, kx, dy, dx);
				if (c == 'Q' || (c == 'B' && dy && dx) || (c == 'R' && !(dy && dx)))
					return (1);
			}
			dx++;
		}
		dy++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	size;
	int	y;
	int	x;

	if (ac < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	size = ac - 1;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (at(av + 1, size, y, x) == 'K')
			{
				if (in_check(av + 1, size, y, x))
					write(1, "Success\n", 8);
				else
					write(1, "Fail\n", 5);
				return (0);
			}
			x++;
		}
		y++;
	}
	write(1, "Fail\n", 5);
	return (0);
}
