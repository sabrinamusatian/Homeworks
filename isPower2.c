#include <stdio.h>

int isPower2(int x)
{
	return (!((x & (~x + 1)) + (~x + 1)));
}

int main()
{
    int x;
    printf("Print x\n");
    scanf("%d", &x);
    printf("isPower2 is %d", isPower2(x));
    return 0;
}
