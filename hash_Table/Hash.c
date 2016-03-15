#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    int val;
    char hash[256];
    struct node *next;
} node;


typedef struct hashChain
{
    node *chain;
} buckets;

typedef struct hashTable
{
    int size;
    buckets *cells;
    int (*callback)(char*);
} hashTable;

hashTable hashT;

typedef int (*callbackFunc)(char *c);

int callFunc(callbackFunc func, char *c)
{
    return func(c);
}


// hash functions

int hashConstant(char *ch)
{
    return 13;
}

int hashCountString(char *key)
{
    int sum = 0;
    while (*key)
    {
        sum += *key;
        key++;
    }
    return sum;
}

int hashRot13(char *key)
{
	long i, hash = 0;
	for(i = 0; i < strlen(key); i++)
	{
		hash += (int)key[i];
		hash -= (hash << 13) | (hash >> 19);
	}
    return hash;
}

node *search(char *key)
{
    long long hashValue = callFunc(hashT.callback, key);
    int position = (hashValue % hashT.size + hashT.size) % hashT.size; // to make it positive

    node *cur = hashT.cells[position].chain;
    while (cur->next != NULL)
    {
        node *temp = cur->next;
        if (strcmp(temp->hash,key) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }

    return cur;
}

int createHashTable(int(*func)(char*), int size)
{
    hashT.cells = (buckets*)malloc(size * sizeof(buckets));
    if (hashT.cells == NULL)
    {
        printf("Malloc failed in create\n");
        return -1;
    }

    int i;
    hashT.size = size;
    hashT.callback = func;

    for (i = 0; i < size; i++)
    {
        hashT.cells[i].chain = malloc(sizeof(node));
        if (hashT.cells[i].chain == NULL)
        {
            printf("Malloc failed in create\n");
            return -1;
        }
        hashT.cells[i].chain->next = NULL;
        hashT.cells[i].chain->val = 0;
    }
    return 0;
}

void deleteHashTable()
{
    int i;
    int size = hashT.size;
    for (i = 0; i < size; i++)
    {
        while (hashT.cells[i].chain != NULL)
        {
            node *temp = hashT.cells[i].chain;
            hashT.cells[i].chain = hashT.cells[i].chain->next;
            free(temp);
        }
    }
    free(hashT.cells);
    return;
}

void add(char *key)
{
    node *cur = search(key);
    if (cur->next == NULL)
    {
        node *newEl = (node*)malloc(sizeof(node));
        if (newEl == NULL)
        {
            printf("Malloc failed in add\n");
            return;
        }
        cur->next = newEl;
        newEl->next = NULL;
        newEl->val = 1;
        strcpy(newEl->hash, key);
    }
    else
    {
        cur = cur->next;
        cur->val++;
    }

    return;
}

void erase(char *key){

    node *cur = search(key);
    if (cur->next == NULL)
    {
        printf("There is not such a string yet\n");
    }
    else
    {
        node *temp = cur->next;
        cur->next = temp->next;
        free(temp);
    }

    return;
}


void statistics()
{
    int i, numberOfCells = 0, numberOfElement = 0 ;
    int sumChain = 0, maxChain = 0, minChain = 1e9, midChain = 0;
    for (i = 0; i < hashT.size; i++)
        {
            node *cur = hashT.cells[i].chain;
            int curLen = -1;
            while (cur != NULL)
            {
                curLen++;
                numberOfElement += cur->val;
                cur = cur->next;
            }

            if (curLen > 0)
            {
                numberOfCells++;
                if(minChain > curLen)
                {
                    minChain = curLen;
                }

            }
            sumChain += curLen;
            if (maxChain < curLen)
            {
                maxChain = curLen;
            }

        }
    if (numberOfCells != 0)
    {
        midChain = sumChain / numberOfCells;
    }

    if (minChain == 1e9)
    {
        minChain = -1;
    }

    printf("Number of used cells in hash Table: %d\n", numberOfCells);
    printf("Number of elements in hash Table: %d\n", numberOfElement);
    printf("Average length of chains in hash Table: %d\n", midChain);
    printf("Minimal length of chains in hash Table: %d\n", minChain);
    printf("Maximal length of chains in hash Table: %d\n", maxChain);

    return;
}

int main()
{
    FILE *fp = freopen("Romeo_and_Juliet.txt", "r", stdin);
    FILE *outp = freopen("output.txt", "w", stdout);
    if (fp == NULL)
    {
        printf("Can't open a file for reading!");
        return 0;
    }
    if (outp == NULL)
    {
        printf("Can't open a file for writing!");
        return 0;
    }
    double start = clock();

    const int size = 65700;

    if (createHashTable(hashCountString, size) != 0)
    {
        printf("Can't make a hashtable!!!!");
        return 0;
    }

    char key[100];
    while (scanf("%s", key) != EOF)
    {
        size_t len = strlen(key) - 1;
        while (len >= 0 && !(isalnum(key[len])))
        {
            key[len] = '\0';
            len--;
        }

        add(key);
    }
    statistics();
    deleteHashTable();
    printf("%f", (clock() - start) / CLOCKS_PER_SEC);

    fclose(stdin);
    fclose(stdout);
    return 0;
}

/*

Constant hash:
Number of used cells in hash Table: 1
Number of elements in hash Table: 27477
Average length of chains in hash Table: 5022
Minimal length of chains in hash Table: 5022
Maximal length of chains in hash Table: 5022
0.499000

Counting stings hash:
Number of used cells in hash Table: 1108
Number of elements in hash Table: 27477
Average length of chains in hash Table: 4
Minimal length of chains in hash Table: 1
Maximal length of chains in hash Table: 28
0.062000

Rot13 hash (effective):
Number of used cells in hash Table: 3760
Number of elements in hash Table: 27477
Average length of chains in hash Table: 1
Minimal length of chains in hash Table: 1
Maximal length of chains in hash Table: 8
0.046000*/
