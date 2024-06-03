#include <stdio.h>
#include <stdlib.h>

struct CircularQueue
{
    int front, rear;
    int *items;
    int size;
};

void initializeQueue(struct CircularQueue *queue, int size)
{
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
    queue->items = (int *)malloc(sizeof(int) * size);
}

int isFull(struct CircularQueue *queue)
{
    return ((queue->rear + 1) % queue->size == queue->front);
}

int isEmpty(struct CircularQueue *queue)
{
    return (queue->front == -1);
}

void enque(struct CircularQueue *queue, int value)
{
    if (isFull(queue))
    {
        printf("Queue is full. Cannot enqueue.\n");
    }
    else
    {
        if (isEmpty(queue))
        {
            queue->front = 0;
        }

        queue->rear = (queue->rear + 1) % queue->size;
        queue->items[queue->rear] = value;

        printf("%d enqueued to the queue\n", value);
    }
}

void dequeue(struct CircularQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty. Cannot dequeue\n");
    }
    else
    {
        printf("%d dequeued from the queue\n", queue->items[queue->front]);

        if (queue->front == queue->rear)
        {
            // If only one element in the queue, reset front and rear
            queue->front = -1;
            queue->rear = -1;
        }
        else
        {
            queue->front = (queue->front + 1) % queue->size;
        }
    }
}

int countElements(struct CircularQueue *queue)
{
    if (isEmpty(queue))
    {
        return 0;
    }
    else
    {
        return (queue->rear - queue->front + 1 + queue->size) % queue->size;
    }
}

void displayQueue(struct CircularQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
    }
    else
    {
        printf("Queue status: ");
        int i = queue->front;
        do
        {
            printf("%d ", queue->items[i]);
            i = (i + 1) % queue->size;
        } while (i != (queue->rear + 1) % queue->size);
        printf("\n");
    }
}

int main()
{
    struct CircularQueue queue;
    int size, choice, value;

    printf("Enter the size of the Circular Queue: ");
    scanf("%d", &size);
    initializeQueue(&queue, size);

    while (1)
    {
        printf("***   Circular Queue Menu:   ***\n");
        printf("1. Enqueue an Element in the Queue.\n");
        printf("2. Dequeue an Element in the Queue.\n");
        printf("3. Count Elements in the Queue.\n");
        printf("4. Display the Queue.\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the Value to Enqueue: ");
            scanf("%d", &value);
            enque(&queue, value);
            break;
        case 2:
            dequeue(&queue);
            break;
        case 3:
            printf("Number of elements in the queue: %d\n", countElements(&queue));
            break;
        case 4:
            displayQueue(&queue);
            break;
        case 5:
            printf("Exiting program\n");
            free(queue.items);
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}
