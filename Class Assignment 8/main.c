#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node
{
    int data;
    struct Node *link;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        // If the list is empty, the new node becomes the head
        printf("The Linked List is empty! Creating One !\n");
        *head = newNode;
    }
    else
    {
        // Traverse the list to find the last node
        struct Node *current = *head;
        while (current->link != NULL)
        {
            current = current->link;
        }

        // Add the new node to the end
        current->link = newNode;
    }
}

// Function to search for a particular node in the linked list
int searchNode(struct Node *head, int target)
{
    struct Node *current = head;
    int position = 1;

    while (current != NULL)
    {
        if (current->data == target)
        {
            return position;
        }
        current = current->link;
        position++;
    }

    return -1; // Node not found
}

// Function to delete a particular node in the linked list
int deleteNode(struct Node **head, int target)
{
    struct Node *prev = NULL;
    struct Node *temp = *head;
    int position = 1;

    while (temp != NULL)
    {
        if (temp->data == target)
        {
            if (prev == NULL)
            {
                // If the node to be deleted is the head
                *head = temp->link;
            }
            else
            {
                prev->link = temp->link;
            }
            free(temp);
            return position; // Node deleted successfully
        }
        position++;
        prev = temp;
        temp = temp->link;
    }

    return -1; // Node not found
}

// Function to display the linked list
void display(struct Node *head)
{
    struct Node *current = head;
    if (current != NULL)
    {
        while (current != NULL)
        {
            printf("%d -> ", current->data);
            current = current->link;
        }
        printf("NULL\n");
    }
    else
    {
        printf("It is empty !!!\n");
    }
}

int main()
{
    int choice, tempData, searchValue, result;
    struct Node *head = NULL;

    printf("*** Singly Linked List ***\n");
    printf("1. Insert Node from the End in the Linked List.\n");
    printf("2. Delete Node from the Linked List.\n");
    printf("3. Search from a Particular Node in the Linked List.\n");
    printf("4. Display the Nodes in the Linked List.\n\n");
    while (1)
    {
        printf("Enter your choice = ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data of the node to insert = ");
            scanf("%d", &tempData);
            insertAtEnd(&head, tempData);
            printf("%d is added in the Linked List successfully! \n", tempData);
            break;

        case 2:
            printf("Enter the data to delete from the Linked List = ");
            scanf("%d", &tempData);
            result = deleteNode(&head, tempData);
            if (result != -1)
            {
                printf("%d is deleted from the Linked List successfully from the position %d! \n", tempData, result);
            }
            else
            {
                printf("%d data not found\n", tempData);
            }
            break;

        case 3:
            printf("Enter the data you want to search in the Linked List = ");
            scanf("%d", &searchValue);
            result = searchNode(head, searchValue);
            if (result != -1)
            {
                printf("Node with data %d found at position %d\n", searchValue, result);
            }
            else
            {
                printf("Node not found\n");
            }
            break;

        case 4:
            printf("The Linked List : \n");
            display(head);
            break;

        default:
            printf("Invalid Choice");
            break;
        }
    }

    return 0;
}
