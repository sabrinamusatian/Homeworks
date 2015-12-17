#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node
{
    int val;
    long long hash;
    struct node *next;
}node;


typedef struct hashChain
{
    node *chain;
}buckets;

typedef struct hashTable
{
    int size;
    buckets *cells;
    int (*callback)(char*);
}hashTable;

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
        if (temp->hash == hashValue)
        {
            return cur;
        }
        cur = cur->next;
    }

    return cur;
}

void createHashTable(int(*func)(char*), int size)
{
    hashT.cells = (buckets*)malloc(size * sizeof(buckets));
    if (hashT.cells == NULL)
    {
        printf("Malloc failed in create\n");
        return;
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
            return;
        }
        hashT.cells[i].chain->next = NULL;
        hashT.cells[i].chain->val = 0;
    }
    return;
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

void set(char *key, int x)
{
    node *cur = search(key);
    if (cur->next == NULL)
    {
        node *newEl = (node*)malloc(sizeof(node));
        if (newEl == NULL)
        {
            printf("Malloc failed in set\n");
            return;
        }
        cur->next = newEl;
        newEl->next = NULL;
        newEl->val = x;
        newEl->hash = callFunc(hashT.callback, key);
    }
    else
    {
        cur = cur->next;
        x = cur->val + x;
        cur->val = x;
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
    freopen("Romeo_and_Juliet.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    double start = clock();

    const int size = 65700;

    createHashTable(hashCountString, size);

    char key[100];
    while (scanf("%s", key) != EOF)
    {
        size_t len = strlen(key) - 1;
        while (len >= 0 && !(isalnum(key[len])))
        {
            key[len] = '\0';
            len--;
        }
        set(key, 1);
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
Average length of chains in hash Table: 1
Minimal length of chains in hash Table: 1
Maximal length of chains in hash Table: 1
0.031000

Counting stings hash:
Number of used cells in hash Table: 1108
Number of elements in hash Table: 27477
Average length of chains in hash Table: 1
Minimal length of chains in hash Table: 1
Maximal length of chains in hash Table: 1
0.046000

Rot13 hash (effective):
Number of used cells in hash Table: 3760
Number of elements in hash Table: 27477
Average length of chains in hash Table: 1
Minimal length of chains in hash Table: 1
Maximal length of chains in hash Table: 3
0.031000*/
