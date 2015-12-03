#include <stdio.h>

int bitXor(int x, int y)
{
    int cur =(~(x&y))&(~((~x)&(~y)));
    return cur;
}

int main()
{
    int x,y;
    printf("Print x and y for bitXor\n");
    scanf("%d %d", &x, &y);
    printf("bitXor: %d\n",bitXor(x,y));
    return 0;
}
