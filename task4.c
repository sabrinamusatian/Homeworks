#include <stdio.h>

int main()
{
    int n, num, i;
    printf("Print number of elements in the array\n");
    scanf("%d", &n);
    num = 0; // counter of zero elements in the array
    for (i = 0; i < n; i++)
    {
        printf("Print next element of the array\n");
        int current; // current element of the array
        scanf("%d", &current);
        if (current == 0)
        {
            num++;
        }
    }
    printf("Number of zero elements: %d", num);
    return 0;
}
