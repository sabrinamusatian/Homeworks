#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
	int field;
	struct node *next;
} node;



node* getLast(node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    while (head->next)
    {
        head = head->next;
    }
    return head;
}

void add(node **head, int value)
{
    node *temp = (node*) malloc(sizeof(node));
    if (temp == NULL)
    {
        printf("malloc failed in add\n");
        return;
    }
    temp->field = value;
    if (*head == NULL)
    {
	temp->next = *head;
	*head = temp;
	printf("The element has been added\n");
        return;
    }
    else
    {
        node *last = getLast(*head);
        temp->next = NULL;
        last->next = temp;
        printf("The element has been added\n");
    }
    return;
}

void rem(node **head, int value)
{
    node *temp = *head;
    node *previous = NULL;
    int check = 0;
    while (temp != NULL)
    {
        if (temp->field == value)
        {
            check = 1;
            if (previous != NULL)
            {
                previous->next = temp->next;
            }
            else
            {
                *head = temp->next;
            }
            free(temp);
            printf("Element has been removed\n");
            return;
        }
        else
        {
            previous = temp;
            temp = temp->next;
        }
    }
    if (check == 0)
    {
        printf("Element has not been found in the list\n");
    }
    return;
}

void print(node *head)
{
    if (head == NULL)
    {
		printf("List is empty\n");
		return;
    }

    while (head != NULL)
    {
        printf("%d ",head->field);
        head = head->next;
    }
    printf("\n");
    return;
}

void clear(node *head)
{
    node *temp;
    while (head != NULL)
    {
        temp = head;
        head =(head)->next;
        free(temp);
    }
}

void createRing(node **head)
{
    if (*head == NULL)
    {
        printf("The list is empty. It cannot be a ring\n");
        return;
    }
    node *last = getLast(*head);
    last->next = (*head);
}

void checkRing(node **head)
{
	if (*head == NULL)
	{
		printf("The list is empty. It cannot be a ring\n");
		return;
	}

	node *temp1 = *head, *temp2 = (*head)->next;

	while (temp2->next && temp2->next->next && temp1 != temp2)
    	{
		temp2 = temp2->next->next;
		temp1 = temp1->next;
	}
	if (temp1 == temp2)
	{
		printf("It is a ring\n");
		return;
	}
	printf("It is not a ring\n");
	return;
}

int main()
{
    node *head = NULL;
    int val, check = 0;
	char c;
	while (check == 0)
    	{
		scanf("%c", &c);
		switch(c)
		{
			case 'a':
				scanf("%d", &val);
				add(&head, val);
			break;

			case 'r':
				scanf("%d", &val);
				rem(&head, val);
			break;

			case 'p':
				print(head);
			break;

			case 's':
        			createRing(&head);
            		break;

            		case 'c':
                		checkRing(&head);
            		break;

			case 'q':
				clear(head);
				check = 3;
			break;
		}
	}

    return 0;
}
