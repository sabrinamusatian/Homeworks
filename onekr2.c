#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void one()
{
    char cur;
    scanf("%c\n", &cur);
    char *s;
    gets(s);
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] != cur)
        {
            printf("%c", s[i]);
        }
    }
    return;
}
