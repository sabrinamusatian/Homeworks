#include <stdio.h>

int main()
{
    int n,i;
    printf("Print number of elements in the array\n");
    scanf("%d", &n);
    int a[n];
    for (i = 0; i < n; i++)
    {
        printf("Print the next element of the array\n");
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n / 2; i++)
    {
        if (a[i] != a[n - 1 - i])
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
