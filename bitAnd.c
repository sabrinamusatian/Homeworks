#include <stdio.h>

int bitAnd(int x, int y)
{
    int cur = ~((~x)|(~y));
    return cur;
}

int main()
{
    int x,y;
    printf("Print x and y for bitAnd\n");
    scanf("%d %d", &x, &y);
    printf("bitAnd: %d\n",bitAnd(x,y));
    return 0;
}
