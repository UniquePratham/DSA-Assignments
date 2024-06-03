/* Stack Assignment 6.1 - Implement the operations on stack: push, pop, top (show the top), display (the stack). */
#include <stdio.h>
#include <stdlib.h>
int top = -1, max_stack_size;
void stackfull()
{
    printf("Stack is Full !\n");
}
void stackempty()
{
    printf("Stack is Empty !\n");
};
void stackpush(int *stack, int item)
{
    if (top >= max_stack_size - 1)
    {
        return stackfull();
    };
    stack[++top] = item;
};
int stackpop(int *stack)
{
    if (top == -1)
    {
        stackempty();
        return -1;
    };
    return stack[top--];
};

void printstack(int *stack)
{
    printf("Stack => ");
    for (int i = 0; i <= top; i++)
    {
        if (i == top)
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
    printf("\nEnter the Size of the Stack = ");
    scanf("%d", &max_stack_size);
    int *stack = (int *)calloc(max_stack_size, sizeof(int));
    while (1)
    {
        printf("*** Stack Operations ***\n");
        printf("1. Push an item in the stack\n");
        printf("2. Pop an item from the stack\n");
        printf("3. Print the array/stack !\n");
        printf("4. Print the top item !\n");
        printf("5. Exit\n");
        printf("Enter your Choice = ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the element/integer you want to push = ");
            scanf("%d", &item);
            stackpush(stack, item);
            if (top < max_stack_size - 1)
            {
                printf("Item %d is pushed successfully !\n", item);
                printstack(stack);
            }
            else if (top == max_stack_size - 1)
            {
                printstack(stack);
            }
            break;
        case 2:
            returnitem = stackpop(stack);
            if (top >= 0)
            {
                printf("The Last item you added %d was popped.\n", returnitem);
                printstack(stack);
            }
            else if (top == -1 && returnitem != -1)
            {
                printf("The Last item you added %d was popped.\n", returnitem);
                stackempty();
            }
            break;

        case 3:
            if (top >= 0)
            {
                printstack(stack);
            }
            else
            {
                stackempty();
            }
            break;

        case 4:
            if (top == -1)
            {
                stackempty();
            }
            else
            {
                printf("The top item of the stack = %d\n", stack[top]);
            }
            break;
        case 5:
            free(stack);
            exit(0);

        default:
            printf("Invalid Choice!");
            exit(0);
            break;
        }
    }
    free(stack);
}