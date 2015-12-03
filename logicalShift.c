#include <stdio.h>

int logicalShift(int x, int n)
{
	int temp = 1;
	x = x >> n;
	temp = (((~(temp << 31)) >> n) << 1) + 1;
	temp = temp & x;
	return temp;
}

int main()
{
    int x, n;
    printf("Print x and n\n");
    scanf("%d %d", &x, &n);
    printf("logicalShift is %d", logicalShift(x, n));
    return 0;
}
