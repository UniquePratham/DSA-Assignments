// Write a menu driven C program to
// a) insert n keys generated randomly to insert in a binary search tree.
// b) print the BST by  inorder traversal to verify that created BST is correct.
// c) compute and print the height of the BST created.

#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node with a given key
struct Node *createNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into a binary search tree
struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Function to perform inorder traversal of the BST
void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Function to calculate the height of the BST
int height(struct Node *root)
{
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int main()
{
    struct Node *root = NULL;
    int choice, n, key, flag = 0;

    do
    {
        printf("*** BST Operations Menu: ***\n\n");
        printf("1. Insert n keys randomly\n");
        printf("2. Print BST by inorder traversal\n");
        printf("3. Compute and print the height of BST\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the number of keys (n): ");
            scanf("%d", &n);
            printf("Inserting %d keys randomly between 0 to 99...\n\n", n);
            for (int i = 0; i < n; ++i)
            {
                key = rand() % 100; // Generating random keys between 0 and 99
                root = insert(root, key);
            }
            flag = 1;
            break;
        case 2:
            if (flag != 0)
            {
                printf("Inorder traversal of BST: ");
                inorderTraversal(root);
            }
            else
            {
                printf("First, create the BST and try again !!!");
            }
            printf("\n\n");
            break;
        case 3:
            if (flag != 0)
            {
                printf("Height of BST: %d\n\n", height(root));
            }
            else
            {
                printf("First, create the BST and try again !!!\n\n");
            }
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
