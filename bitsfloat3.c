#include <stdio.h>

int main()
{
    float F;
    int* pointI;
    scanf("%f", &F);
    pointI = (int*)&F;
    int mant, sign, e;
    mant = *pointI & (((1 << 31) >> 31) ^ ((1 << 31) >> 8));
    sign = (*pointI >> 31) & 1;
    e = (*pointI >> 23) & 255;
    printf("float = (-1)^%d * 1.%d * 2^(%d-127)", sign, mant, e);
    return 0;
}
