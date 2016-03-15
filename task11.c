#include <stdio.h>

int main()
{
    int i, n;
    printf("Print number for Fibonacci ");
    scanf("%d", &n);
    int f[n];
    f[0] = 1;
    f[1] = 2;
    for (i = 2; i < n; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
    }
    printf("Fibonacci number is %d", f[n - 1]);
    return 0;
}
