/* Infix Expression and Postfix Expression Assignment*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack implementation
typedef struct
{
    int top;
    char items[MAX_SIZE];
} Stack;

void initialize(Stack *stack)
{
    stack->top = -1;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, char item)
{
    if (stack->top == MAX_SIZE - 1)
    {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = item;
}

char pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

char peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int getPrecedence(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    Stack stack;
    initialize(&stack);

    int i = 0, j = 0;
    while (infix[i] != '\0')
    {
        char token = infix[i];

        if (isdigit(token))
        {
            postfix[j++] = token;
        }
        else if (token == '(')
        {
            push(&stack, token);
        }
        else if (token == ')')
        {
            while (!isEmpty(&stack) && peek(&stack) != '(')
            {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // Pop '('
        }
        else if (isOperator(token))
        {
            while (!isEmpty(&stack) && getPrecedence(token) <= getPrecedence(peek(&stack)))
            {
                postfix[j++] = pop(&stack);
            }
            push(&stack, token);
        }

        i++;
    }

    while (!isEmpty(&stack))
    {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

void postfixToInfix(char postfix[], char infix[])
{
    Stack stack;
    initialize(&stack);

    int i = 0, j = 0;
    while (postfix[i] != '\0')
    {
        char token = postfix[i];
        if (isdigit(token))
        {
            push(&stack, token);
        }
        else if (isOperator(token))
        {
            if (stack.top > 0)
            {
                char operand1 = pop(&stack);
                char operand2 = pop(&stack);
                infix[j++] = '(';
                infix[j++] = operand2;
                infix[j++] = token;
                infix[j++] = operand1;
                infix[j++] = ')';
                infix[j] = '\0';
            }
            else if (stack.top == 0)
            {
                char operand = pop(&stack);
                for (int k = j; k >= 0; k--)
                {
                    infix[k + 1] = infix[k];
                }
                j++;
                infix[0] = '(';
                infix[j++] = token;
                infix[j++] = operand;
                infix[j++] = ')';
                infix[j] = '\0';
            }
            else if (stack.top == -1)
            {
                int k;
                int count = 0;
                for (k = 0; k < j; k++)
                {
                    if (infix[k] == ')' && infix[k + 1] == '(')
                    {
                        for (int x = j; x >= k + 1; x--)
                        {
                            infix[x + 1] = infix[x];
                        }
                        j++;
                        infix[k + 1] = token;
                        infix[j] = '\0';
                        count = 1;
                        break;
                    }
                }
            }
        }

        i++;
    }
}

int evaluatePostfix(char postfix[])
{
    Stack stack;
    initialize(&stack);

    int i = 0;
    while (postfix[i] != '\0')
    {
        char token = postfix[i];

        if (isdigit(token))
        {
            push(&stack, token - '0'); // Convert character to integer
        }
        else if (isOperator(token))
        {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (token)
            {
            case '+':
                push(&stack, operand1 + operand2);
                break;
            case '-':
                push(&stack, operand1 - operand2);
                break;
            case '*':
                push(&stack, operand1 * operand2);
                break;
            case '/':
                push(&stack, operand1 / operand2);
                break;
            }
        }

        i++;
    }

    return pop(&stack);
}

int main()
{
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    int result, choice;

    // Choice for expression
    printf("*** Choose the Expression! ***\n");
    printf("1. Enter Infix Expression!\n");
    printf("2. Enter Postfix Expression!\n");
    printf("Enter Your Choice = ");

    // Use scanf for both integer input and consume the newline character
    if (scanf(" %d", &choice) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    // Consume the remaining newline character
    getchar();

    switch (choice)
    {
    case 1:
        // Input Infix expression
        printf("Enter Infix Expression: ");
        fgets(infix, MAX_SIZE, stdin);
        printf("\n\nInfix Expression: %s\n", infix);
        // Convert infix to postfix
        infixToPostfix(infix, postfix);
        printf("Postfix Expression: %s\n\n", postfix);
        // Evaluate postfix expression
        result = evaluatePostfix(postfix);
        printf("Result of Postfix Expression: %d\n\n", result);
        break;
    case 2:
        // Input Postfix expression
        printf("Enter Postfix Expression: ");
        fgets(postfix, MAX_SIZE, stdin);
        printf("\n\nPostfix Expression: %s\n", postfix);
        // Convert postfix to infix
        postfixToInfix(postfix, infix);
        printf("Infix Expression: %s\n\n", infix);
        result = evaluatePostfix(postfix);
        printf("Result of Postfix Expression: %d\n\n", result);
        break;
    default:
        printf("Invalid Choice!!!");
        break;
    }

    return 0;
}