#include <stdio.h>

int main(void)
{int a = 2147483647;
a = a  + 2147483647 + 120;
printf("%d\n", a);
	return 0;
}