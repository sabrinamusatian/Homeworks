#include <stdio.h>
#include <stdlib.h>


void float1(float F)
{
    union floatbits
    {
       int bitsInt;
       float bitsFloat;
    }result;
    result.bitsFloat = F;
    int mant, e, sign;
    mant = result.bitsInt & (((1 << 31) >> 31) ^ ((1 << 31) >> 8));
    sign = (result.bitsInt >> 31) & 1;
    e = (result.bitsInt >> 23) & 255;
    myprint(sign, mant, e);
    return;
}

void float2(float F)
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

    result.bitsFloat = F;
    parts.mant = result.bitsInt & (((1 << 31) >> 31) ^ ((1 << 31) >> 8));
    parts.sign = (result.bitsInt >> 31) & 1;
    parts.e = (result.bitsInt >> 23) & 255;
    myprint(parts.sign, parts.mant, parts.e);
    return;
}

void float3(float F)
{
    int* pointI;
    pointI = (int*)&F;
    int mant, sign, e;
    mant = *pointI & (((1 << 31) >> 31) ^ ((1 << 31) >> 8));
    sign = (*pointI >> 31) & 1;
    e = (*pointI >> 23) & 255;
    myprint(sign, mant, e);
    return;
}

void myprint(int sign,int mant,int e)
{
    int i = 0;
    if (e == 0xff)
    {
        if (mant == 0)
        {
            printf((sign ? "-inf" : "+inf"));
        }
        else
        {
            printf("NaN");
        }
    }
    else
    {
       printf("float = (-1)^%d * 1.%d * 2^(%d-127)", sign, mant, e);
    }
    printf("\n");
}

int main()
{
    float f1, f2;
    scanf("%f %f", &f1, &f2);
    float1(f1 / f2);
    float2(f1 / f2);
    float3(f1 / f2);
    return 0;
}
