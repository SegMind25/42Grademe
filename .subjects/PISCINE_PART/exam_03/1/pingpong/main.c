#include <unistd.h>

void pingpong(int n);

int main(void)
{
	pingpong(1);
	pingpong(3);
	pingpong(5);
	pingpong(15);
	pingpong(999);
	pingpong(998);
	return (0);
}
