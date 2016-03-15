#include <stdio.h>
#include <math.h>

int simple(int x)
{
    int sq = (int)sqrt(x);
    int i;
    for (i = 2; i <= sq; i++)
    {
        if (x % i == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int i, n;
    printf("Print number\n");
    scanf("%d", &n);
    printf("Simple numbers not greater than %d are: ", n);
    for (i = 1; i <= n; i++)
    {
        if (simple(i) == 0)
        {
            printf("%d ", i);
        }
    }
    return 0;
}
