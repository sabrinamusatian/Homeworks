#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void three()
{
    FILE *f1 = fopen("input.txt", "r");
    if (f1 == NULL)
    {
        printf("File was not open");
        return;
    }
    FILE *f2 = fopen("output.txt", "w");
    if (f2 == NULL)
    {
        printf("File to write to was not open");
        return;
    }
    char s[255];
    while(fgets(s, 255, f1));
    {
        int i;
        for (i = 0; i < strlen(s) - 1; i++)
        {
            if (s[i] == '/' && s[i + 1] == '/')
            {
                int j;
                for (j = i + 2; j < strlen(s); j++)
                {
                    fprintf(f2, "%c", s[j]);
                }
                fprintf(f2, "\n");
                break;
            }
        }
    }
    fclose(f1);
    fclose(f2);
    return;
}
