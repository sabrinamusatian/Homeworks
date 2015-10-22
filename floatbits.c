#include <stdio.h>

int main()
{
    union floatbits
    {
       int bitsInt;
       float bitsFloat;
    }result;
    scanf("%f", &result.bitsFloat);
    int mant, e, sign;
    mant = result.bitsInt & (((1 << 31) >> 31) ^ ((1 << 31) >> 8));
    sign = (result.bitsInt >> 31) & 1;
    e = (result.bitsInt >> 23) & 255;
    printf("float = (-1)^%d * 1.%d * 2^(%d-127)", sign, mant, e);
    return 0;
}
