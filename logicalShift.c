#include <stdio.h>

int logicalShift (int x, int n)
{
    int current = (~(1 << 31)) >> n;
    x = x >> n;
    return x & current;
}

int main()
{
    int x, n;
    printf("Print x and n\n");
    scanf("%d %d", &x, &n);
    printf("logicalShift is %d", logicalShift(x, n));
    return 0;
}
