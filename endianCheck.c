 #include <stdio.h>

union machine
{
    int x;
    char bytes[3];
};

int endian()
{
    union machine check;
    check.x = 1;
    return check.bytes[0];
}

int main()
{
    printf("Your machine is %d", endian());
    return 0;
}
