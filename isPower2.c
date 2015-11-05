#include <stdio.h>

int isPower2(int x)
{
    int temp;
    temp = (!((1 << 31) & x)) & (!(x & (x + (~0)))) & (!!x);
    return temp;
}

int main()
{
    int x;
    printf("Print x\n");
    scanf("%d", &x);
    printf("isPower2 is %d", isPower2(x));
    return 0;
}

