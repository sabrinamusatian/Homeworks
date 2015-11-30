#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void bubble_sort (int *x, int n) //n^2
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            int temp;
            if (x[j + 1] < x[j])
            {
                int temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;
            }
        }
    }
    printf("\n");
    return;
}

void  array_sort (int *x, int n) // n
{
    int i, j = 0;
    int maxim = 100; // max value of variable in our array

    int *temp = (int*) malloc(maxim * sizeof(int));

    if (temp == NULL)
    {
        printf("malloc failed in array_sort\n");
        return;
    }

    for (i = 0; i < 100; i++)
    {
        temp[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        temp[x[i]]++;
    }
    i = 0;
    while (j < n)
    {
        while (temp[i] > 0)
        {
            x[j] = i;
            temp[i]--;
            j++;
        }
        i++;
    }
    free(temp);
    return;
}

// The whole piece just for the merge sort with all helper functions

// Helper function for finding the max of two numbers
int max(int x, int y)
{
    if(x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

void merge_helper(int *input, int left, int right, int *temp)
{
    if(right == left + 1)
    {
        return;
    }
    else
    {
        int i = 0;
        int length = right - left;
        int midpoint = length/2;
        int l = left, r = left + midpoint;

        //sort subarrays
        merge_helper(input, left, left + midpoint, temp);
        merge_helper(input, left + midpoint, right, temp);

        // merge the arrays together
        for(i = 0; i < length; i++)
        {
            if(l < left + midpoint && (r == right || max(input[l], input[r]) == input[r]))
            {
                temp[i] = input[l];
                l++;
            }
            else
            {
                temp[i] = input[r];
                r++;
            }
        }

        for(i = left; i < right; i++)
        {
            input[i] = temp[i - left];
        }
    }
}

int merge_sort(int *input, int size)
{
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL)
    {
        printf("malloc failed in merge\n");
        return;
    }
    merge_helper(input, 0, size, temp);
    free(temp);
    return;
}

int main()
{
    int i, n = 100000000;
    int *x = (int*)malloc(n * sizeof(int));
    if (x == NULL)
    {
        printf("malloc failed in main\n");
        return;
    }

    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        x[i] = rand() % 100; // generate numbers between 0 and 99
    }

    clock_t start, result;
    start = clock();
    merge_sort(x,n);
    result = clock() - start;

    printf("time: %.4f", (double)result/CLOCKS_PER_SEC);

    free(x);
    return 0;
}

/*	size     n       n^2     n*logn
    5       0.0000	0.0000	 0.00000
	10  	0.0000 	0.0000 	 0.0000
	100 	0.0000	0.0000	 0.0000
	1k  	0.0000 	0.0150   0.0000
	10k 	0.0000	0.5930	 0.0000
	100k	0.0000 	50.8560  0.0470
	1M  	0.0160 	n/a  	 0.4050
	10M 	0.0780	n/a      4.0400
    100M	0.6400	n/a      40.2230 */
