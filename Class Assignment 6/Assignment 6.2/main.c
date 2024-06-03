/* Stack Assignment 6.2 - A stack -sortable permutation is one, where given a set of integers, and an empty stack s, using the push and pop operations on the given set of integers, the given set of integers can be sorted. Note that when a pop operation is performed it is an output. if it is possible to generate the sorted sequence we say, it is stack sortable else no. */
#include <stdio.h>
#include <stdlib.h>

int topA = -1, topB = -1, max_stack_size;

void stackfull()
{
    printf("Stack is Full !");
    exit(0);
}

void stackempty()
{
    printf("Stack is Empty !");
    exit(0);
}

void stackpush(int *stack, int *top, int item)
{
    if (*top >= max_stack_size - 1)
    {
        stackfull();
    }
    stack[++(*top)] = item;
}

int stackpop(int *stack, int *top)
{
    if (*top == -1)
    {
        stackempty();
    }
    return stack[(*top)--];
}

void printstack(int *stack, int *top)
{
    printf("Stack => ");
    for (int i = 0; i <= *top; i++)
    {
        if (i == *top)
        {
            printf("%d", stack[i]);
        }
        else
        {
            printf("%d,", stack[i]);
        }
    }
    printf("\n");
}

int main()
{
    int choice, item, returnitem;
    printf("Enter the Size of the Stack = ");
    scanf("%d", &max_stack_size);

    int *stackA = (int *)calloc(max_stack_size, sizeof(int));
    int *stackB = (int *)calloc(max_stack_size, sizeof(int));

    for (int i = 0; i < max_stack_size; i++)
    {
        if (i == 0)
        {
            printf("Enter First Element = ");
            scanf("%d", &item);
            stackpush(stackA, &topA, item);
        }
        else
        {
            printf("Enter Element = ");
            scanf("%d", &item);
            while (topA >= 0 && item > stackA[topA])
            {
                returnitem = stackpop(stackA, &topA);
                stackpush(stackB, &topB, returnitem);
            }
            stackpush(stackA, &topA, item);
        }
    }

    // Handle remaining elements in stackA
    while (topA >= 0)
    {
        returnitem = stackpop(stackA, &topA);
        stackpush(stackB, &topB, returnitem);
    }

    // Check whether the sequence is stack-sortable
    int sorted = 1;
    for (int i = 1; i < max_stack_size; i++)
    {
        if (stackB[i] < stackB[i - 1])
        {
            sorted = 0;
            break;
        }
    }

    // Print the result
    if (sorted)
    {
        printf("The Sequence is Stack-Sortable.\n");
        printf("Sorted ");
    }
    else
    {
        printf("The Sequence is not Stack-Sortable.\n");
        printf("Unsorted ");
    }
    printstack(stackB, &topB);
    // Free allocated memory
    free(stackA);
    free(stackB);

    return 0;
}
