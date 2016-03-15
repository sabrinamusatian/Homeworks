#include <stdio.h>

int fitsBits(int x, int n) {
    int cur = ((x << (33 + ~n)) >> (33 + ~n));
    return !(cur + ~x + 1);
}

int main()
{
    int x, n;
    printf("Print x and n for fitsBits\n");
    scanf("%d %d", &x, &n);
    printf("fitsBits: %d", fitsBits(x, n));
    return 0;
}
