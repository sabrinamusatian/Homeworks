#include <stdio.h>

int degree(int x, int s, int m, int n)
{
    if (2*m <= n)
    {
        x = x*x;
        m = 2*m;
        degree(x, s, m, n);
    }
    int i;
    for (i = m + 1; i <= n; i++)
    {
        x = x*s;
    }

    return x;
}

int main()
{
    int s, n;
    scanf("%d %d",&s, &n);
    int m = 1; // counter for current degree
    printf("Degree %d in %d is: %d", s, n, degree(s, s, m, n));
    return 0;
}
