#include <stdio.h>

int getByte(int x, int n)
{
    return (x >> (n << 3) & (0xFF));
}

int main()
{
    int x, n;
    printf("Print x and n for getByte\n");
    scanf("%d", &x, &n);
    printf("getByte: %d", getByte(x, n));
    return 0;
}
