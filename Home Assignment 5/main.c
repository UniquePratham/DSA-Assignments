// Implement a Double ended queue using doubly linked list.
// It should have the following menu:
// 1. Insert at Front (a)
// 2. Insert at End (a)
// 3. Remove from Front (a)
// 4. Remove from End (a)
// 5. Display the content of Queue
#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

// Queue structure
struct Queue
{
    struct Node *front;
    struct Node *rear;
};

// Function to initialize an empty queue
void initializeDeque(struct Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

// Function to insert a node at the front of the queue
void insertFront(struct Queue *queue, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (queue->front == NULL)
    {
        // If queue is empty
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        newNode->next = queue->front;
        queue->front->prev = newNode;
        queue->front = newNode;
    }

    printf("Inserted %d at the front.\n\n", data);
}

// Function to insert a node at the end of the queue
void insertEnd(struct Queue *queue, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (queue->rear == NULL)
    {
        // If queue is empty
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        newNode->prev = queue->rear;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    printf("Inserted %d at the end.\n\n", data);
}

// Function to remove a node from the front of the queue
void removeFromFront(struct Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty. Nothing to remove from the front.\n\n");
        return;
    }

    struct Node *temp = queue->front;
    queue->front = temp->next;

    if (queue->front == NULL)
    {
        // If the queue becomes empty after removal
        queue->rear = NULL;
    }
    else
    {
        queue->front->prev = NULL;
    }

    printf("Removed %d from the front.\n\n", temp->data);
    free(temp);
}

// Function to remove a node from the end of the queue
void removeFromEnd(struct Queue *queue)
{
    if (queue->rear == NULL)
    {
        printf("Queue is empty. Nothing to remove from the end.\n\n");
        return;
    }

    struct Node *temp = queue->rear;
    queue->rear = temp->prev;

    if (queue->rear == NULL)
    {
        // If the queue becomes empty after removal
        queue->front = NULL;
    }
    else
    {
        queue->rear->next = NULL;
    }

    printf("Removed %d from the end.\n\n", temp->data);
    free(temp);
}

// Function to display the content of the queue
void displayDeque(struct Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty.\n\n");
        return;
    }

    struct Node *current = queue->front;
    printf("Queue: ");
    while (current != NULL)
    {
        if (current->next != NULL)
        {
            printf("%d , ", current->data);
            current = current->next;
        }
        else
        {
            printf("%d ", current->data);
            current = current->next;
        }
    }
    printf("\n\n");
}

// Main function with the menu
int main()
{
    struct Queue queue;
    initializeDeque(&queue);

    int choice, data;

    do
    {
        printf("*** Double Ended Queue Using Doubly Linked List ***\n\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at End\n");
        printf("3. Remove from Front\n");
        printf("4. Remove from End\n");
        printf("5. Display the content of Queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at the front: ");
            scanf("%d", &data);
            insertFront(&queue, data);
            break;
        case 2:
            printf("Enter data to insert at the end: ");
            scanf("%d", &data);
            insertEnd(&queue, data);
            break;
        case 3:
            removeFromFront(&queue);
            break;
        case 4:
            removeFromEnd(&queue);
            break;
        case 5:
            displayDeque(&queue);
            break;
        case 6:
            printf("Exiting the program.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
