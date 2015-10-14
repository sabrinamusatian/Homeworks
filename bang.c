#include <stdio.h>

int bang(int x)
{
   int negativeX = ~x + 1;
   int temprorary = ((x >> 31) & 1) | ((negativeX >> 31) & 1);
   return temprorary ^ 1;
}

int main()
{
    int x;
    printf("Print x\n");
    scanf("%d", &x);
    printf("bang is %d", bang(x));
    return 0;
}
