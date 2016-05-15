#include <stdio.h>
#include <string.h>

#define NUM_OF_COMMANDS 9
#define SIZE 1048576
#define LINES 1000
#define NAME 50

typedef struct
{
    int type;
    union
    {
        int number;
        char lbl[NAME];
    } arg;
} commands;

commands instructions[LINES];
char *commandsName [NUM_OF_COMMANDS] = {"ld", "st", "ldc", "add", "sub", "cmp", "jmp", "br", "ret"}; // command names

// enumerate all command for simplicity
typedef enum
{
	LD,
	ST,
	LDC,
	ADD,
	SUB,
	CMP,
	JMP,
	BR,
	RET,
} command;

typedef struct
{
    char name[NAME];
    size_t line;
} typeLabel;

typeLabel label[LINES];


int data[SIZE];
int stack[SIZE];
char str[255];
char stringInstruction[NAME];
char stArg[NAME];
int arrLabel = 0;
int countLines = 0;


int find(char *stInstr, char *str, int i)
{
    while (str[i] == ' ')
    {
        i++;
    }
    if ((str[i] == ';') || (str[i] == '\0'))
    {
        return i;
    }
    int j = 0;
    while ((isalpha(str[i])) || (isdigit(str[i])) || (str[i] == '-'))
    {
        stInstr[j] = str[i];
        i++;
        j++;
    }
    stInstr[j] = '\0';
    return i;
}

// determine number of command
int whatCommand(char *stInstr)
{
    int num;
    for (num = 0; num < NUM_OF_COMMANDS; num++)
    {
        if (strcmp(stInstr, commandsName[num]) == 0)
        {
            return num;
        }
    }
}

int readFile(FILE *file)
{
    while (!feof(file))
    {
        fgets(str, 255, file);
        int i = 0;
        while (str[i] == ' ')
        {
            i++;
        }
        if ((str[i] == ';') || (str[i] == '\n') || (str[i] == '\0'))
        {
            continue;
        }
        i = 0;
        i = find(stringInstruction, str, i);
        instructions[countLines].type = whatCommand(stringInstruction);
        int k;
        while (str[i] == ' ')
        {
            i++;
        }
        if (str[i] == ':')
        {
            strcpy(label[arrLabel].name, stringInstruction);
            label[arrLabel].line = countLines;
            arrLabel++;
            i++;
            if (str[i] == '\0')
            {
                continue;
            }
            else
            {
                i = find(stringInstruction, str, i);
            }
        }
        while (str[i] == ' ')
        {
            i++;
        }
        instructions[countLines].type = whatCommand(stringInstruction);
        int j = 0;
        i = find(stArg, str, i);
        if (isdigit(stArg[0]) || (stArg[0] == '-'))
        {
            instructions[countLines].arg.number = atoi(stArg);
        }
        else
        {
            strcpy(instructions[countLines].arg.lbl, stArg);
        }
        countLines++;
   }
   return 1;
}

int run(FILE *file)
{
    int SP = -1;
    int i = -1;
    int arg;
    char lbl[NAME];
    int a, b, j;
    while (1)
    {
       i++;
       switch (instructions[i].type)
       {
           case LD:
               SP++;
               arg = instructions[i].arg.number;
               if ((SP < 0) || (SP > SIZE) || (arg > SIZE) || (arg < 0))
               {
                  printf("ERROR_IN_LD");
                  return 0;
               }
               stack[SP] = data[arg];
               break;
           case ST:
               arg = instructions[i].arg.number;
               if ((SP < 0) || (SP > SIZE) || (arg > SIZE) || (arg < 0))
               {
                  printf("ERROR_IN_ST");
                  return 0;
               }
               data[arg] = stack[SP];
               SP--;
               break;
           case LDC:
               SP++;
               arg = instructions[i].arg.number;
               if ((SP < 0) || (SP > SIZE))
               {
                   printf("ERROR_IN_LDC");
                   return 0;
               }
               stack[SP] = arg;
               break;
           case ADD:
               if (SP < 1)
               {
                   printf("ERROR_IN_ADD");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a + b;
               break;
           case SUB:
                if (SP < 1)
               {
                   printf("ERROR_IN_SUB");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a - b;
               break;
           case CMP:
               if (SP < 1)
               {
                   printf("ERROR_IN_CMP");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a > b ? 1 : a < b ? -1 : 0;
               break;
          case JMP:
               j = 0;
               strcpy(lbl, instructions[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0)
               {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case BR:
               if ((stack[SP] == 0))
               {
                   break;
               }
               j = 0;
               strcpy(lbl, instructions[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0)
               {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case RET:
               printf("result = %d\n", stack[SP]);
               fclose(file);
               return 1;
        }
    }
}

int main()
{
    printf("Enter number of file\n");
    printf(" 1: for fib\n 2: for simple number\n 3: for GCD \n");
    int num;
    FILE *file;
    scanf("%d", &num);
    if (num == 1)
    {
        file = fopen("one.txt", "r");
    }
    else if (num == 2)
    {
        file = fopen("two.txt", "r");
    }
    else if (num == 3)
    {
        file = fopen("three.txt", "r");
    }
    else
    {
        printf("No instruction with this number");
        return 0;
    }
    // check whether we successfully opened a file
    if (file == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    if (!readFile(file))
    {
        fclose(file);
        return 0;
    }
    if (!run(file))
    {
        fclose(file);
    }
    return 0;
}
