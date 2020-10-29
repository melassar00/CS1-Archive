#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value, maxSupport;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *front;
    Node *end;
} LinkedList;

typedef struct Stack
{
    LinkedList *list;
} Stack;

// counters
int brokenCount = 0;
int unbrokenCount = 0;
int finalHeight = 0;

// helper functions taken from post-fix gen practice problems
LinkedList *createLinkedList();
void addToFront(LinkedList *, int);
void removeFront(LinkedList *);
Stack *createStack();
void push(Stack *, int);
void pop(Stack *);

// evaluates the stack and changes the stack when necessary
int evaluate(Stack *);

int main()
{
    // initialize input
    int maxSupport = 0;

    // initialize a stack
    Stack *stack = createStack();

    // initialize an index
    int ind = 1;
    while (maxSupport != -1)
    {
        // user input for max support value
        scanf("%d", &maxSupport);
        if (maxSupport != -1)
        {
            // get the current height of stack if something broke
            int retHeight = evaluate(stack);

            // if evaluate() returned -1 this means that nothing was broken
            if (retHeight == -1)
            {
                push(stack, maxSupport);
                finalHeight++;
            }
            else
            {
                // since something broke, we must print link index and the new height
                printf("Chain broken at link %d. New height is %d.\n", ind, retHeight);
            }
        }
        // increment index
        ind++;
    }

    // print final height, broken count, and unbroken count
    printf("Ending chain height is %d.\n", finalHeight);
    printf("There are %d broken links and %d whole links on the floor.\n", brokenCount, unbrokenCount);
}

int evaluate(Stack *stack)
{
    // initialize temp node and necessary statistic variables
    Node *temp = stack->list->front;
    int broken = 0;
    int index = 0;
    int lastBroke = 0;
    int height = 0;

    // iterate through linked list
    while (temp != NULL)
    {
        // since there will be a new addition to the stack, decrement each nodes support value
        temp->value = temp->value - 1;

        // if the support value is -1, it broke
        if (temp->value == -1)
        {
            lastBroke = index;
            broken++;
        }

        // increment height
        height++;

        // go next in the chain
        temp = temp->next;

        // increment index
        index++;
    }
    int i;

    // if there were any broken chains
    if (broken > 0)
    {
        // iterate until the last broken chain
        for (i = 0; i <= lastBroke; i++)
        {
            // decrement height
            height--;

            // get rid of those chains from the stack
            pop(stack);
        }

        // unbroken chains start 2 indexes after the last broken
        lastBroke += 2;

        // restart temp from front of list
        temp = stack->list->front;

        // iterate through list again to add back chains that fell to support values
        while (temp != NULL)
        {
            temp->value = temp->value + lastBroke;
            temp = temp->next;
        }
    }

    // update total broken on floor
    brokenCount = broken + brokenCount;

    // update total unbroken on floor
    unbrokenCount = unbrokenCount + (lastBroke - broken);

    // update final height
    finalHeight = height;

    // if the chain is broken return the height, else return -1
    return (broken) ? height : -1;
}

void addToFront(LinkedList *list, int maxSupport)
{
    // Create the memroy
    Node *newFront = (Node *)calloc(1, sizeof(Node));

    // Set up the value for the new front node
    newFront->maxSupport = maxSupport;
    newFront->value = maxSupport;
    // The old list front becomes the second element in the list
    // So set the new front's next value to the old front
    newFront->next = list->front;

    // Update the front of the linked list
    list->front = newFront;
}

LinkedList *createLinkedList()
{
    // Create the memory for the linked list
    LinkedList *ret = (LinkedList *)calloc(1, sizeof(LinkedList));

    // Set the front to NULL to signify the list is empty
    ret->front = NULL;

    // Return the created linked list
    return ret;
}

// Function to create a Stack
Stack *createStack()
{
    // Create the memory for the Stack
    Stack *ret = (Stack *)calloc(1, sizeof(Stack));

    // In this implementation a linked list represents the stack
    // Create the linked list for this stack
    ret->list = createLinkedList();

    // Return the created stack
    return ret;
}

// Function to push a value onto the top of the stack
void push(Stack *stk, int value)
{
    // The function is a add to front of a linked list
    // in this stack implementation
    addToFront(stk->list, value);
}

// Function to pop the top of the stack
void pop(Stack *stk)
{
    // Popping the top is the same as removing the front
    // in this implementation of a stack
    removeFront(stk->list);
}

// Function to remove the front of the linked list
void removeFront(LinkedList *list)
{
    // Check if the Linked List is empty
    if (list->front == NULL)
    {
        return;
    }

    // Get the new head
    Node *newFront = list->front->next;

    // Free the old head
    free(list->front);

    // Update the List's head, thereby removing the old head
    list->front = newFront;
}
