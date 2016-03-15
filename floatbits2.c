#include <stdio.h>

int main()
{
    union floatbits
    {
        int bitsInt;
        float bitsFloat;
    }result;

    struct bits
    {
        unsigned sign: 1;
        unsigned e: 8;
        unsigned mant: 23;
    }parts;

    scanf("%f", &result.bitsFloat);
    parts.mant = result.bitsInt & (((1 << 31) >> 31) ^ ((1 << 31) >> 8));
    parts.sign = (result.bitsInt >> 31) & 1;
    parts.e = (result.bitsInt >> 23) & 255;
    printf("float = (-1)^%d * 1.%d * 2^(%d-127)", parts.sign, parts.mant, parts.e);
    return 0;
}
