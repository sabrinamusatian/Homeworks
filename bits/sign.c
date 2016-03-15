#include <stdio.h>

int sign(int x)
{
    int cur = (x >> 31) + (((~x) >> 31) & (!!(x << 1)));
    return cur;
}

int main()
{
    int x;
    printf("Print x for sign\n");
    scanf("%d", &x);
    printf("Sign: %d\n", sign(x));
    return 0;
}
