/* Queue Assignment 7 */
#include <stdio.h>
#include <stdlib.h>
int front = -1, rear = -1, max_Queue_size;
void Queuefull()
{
    printf("Queue is Full !\n");
}
void Queueempty()
{
    printf("Queue is Empty !\n");
};
void Enqueue(int *Queue, int item)
{
    if (rear >= max_Queue_size - 1)
    {
        return Queuefull();
    };
    Queue[++rear] = item;
};
int Dequeue(int *Queue)
{
    if (front == rear)
    {
        Queueempty();
        return -1;
    };
    return Queue[front++];
};

void printQueue(int *Queue)
{
    printf("Queue => ");
    for (int i = front + 1; i <= rear; i++)
    {
        if (i == rear)
        {
            printf("%d", Queue[i]);
        }
        else
        {
            printf("%d,", Queue[i]);
        }
    }
    printf("\n");
}
int main()
{
    int choice, item, returnitem;
    printf("\nEnter the Size of the Queue = ");
    scanf("%d", &max_Queue_size);
    int *Queue = (int *)calloc(max_Queue_size, sizeof(int));
    while (1)
    {
        printf("*** Queue Operations ***\n");
        printf("1. Enqueue an item in the Queue\n");
        printf("2. Dequeue an item from the Queue\n");
        printf("3. Print the Array/Queue !\n");
        printf("4. Print the Front item !\n");
        printf("5. Print the Rear item !\n");
        printf("6. Print the Total Number of Current items !\n");
        printf("7. Exit\n");
        printf("Enter your Choice = ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the element/integer you want to push = ");
            scanf("%d", &item);
            Enqueue(Queue, item);
            if (rear < max_Queue_size - 1)
            {
                printf("Item %d is enqueued successfully !\n", item);
                printQueue(Queue);
            }
            else if (rear >= max_Queue_size - 1)
            {
                printQueue(Queue);
            }
            break;
        case 2:
            returnitem = Dequeue(Queue);
            if (front == rear && returnitem != -1)
            {
                Queueempty();
            }
            else if (front < rear)
            {
                printf("The First item %d is dequeued.\n", returnitem);
                printQueue(Queue);
            }
            break;

        case 3:
            if (front == rear)
            {
                Queueempty();
            }
            else
            {
                printQueue(Queue);
            }
            break;

        case 4:
            if (front == rear)
            {
                Queueempty();
            }
            else
            {
                printf("The Front item of the Queue = %d\n", Queue[front + 1]);
            }
            break;
        case 5:
            if (rear == front)
            {
                Queueempty();
            }
            else
            {
                printf("The Rear item of the Queue = %d\n", Queue[rear]);
            }
            break;
        case 6:
            if ((rear - front) == 0)
            {
                Queueempty();
            }
            else
            {
                printf("The Total Number of Current items = %d\n", rear - front);
            }
            break;
        case 7:
            exit(1);
        default:
            printf("Invalid Choice!");
            exit(0);
            break;
        }
    }
}