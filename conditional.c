#include <stdio.h>

int conditional(int p, int q, int r)
{
    int current = ((((p >> 31) | ((~p + 1) >> 31)) << 31) >> 31);
    return ((current & q) + (~current & r));
}

int main()
{
    int p, q, r;
    printf("Print p, q and r\n");
    scanf("%d %d %d", &p, &q, &r);
    printf("conditional is %d", conditional(p, q, r));
    return 0;
}
