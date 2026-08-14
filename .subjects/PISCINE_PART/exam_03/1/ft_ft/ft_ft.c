#include <unistd.h>
int main(void)
{
	write(1, "42\n", 3);
	return (0);
}
