#include <unistd.h>

void print_nth_char(char *str, int n);

int main(void)
{
	print_nth_char("ABCDEF", 2);
	print_nth_char("PROGRAMMING", 3);
	print_nth_char("HELLOQUAD", 4);
	print_nth_char("ABC", 1);
	print_nth_char("ABCDEF", 0);
	print_nth_char("", 2);
	return (0);
}
