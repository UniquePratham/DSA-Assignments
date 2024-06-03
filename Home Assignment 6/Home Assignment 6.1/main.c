// Write a complete menu-driven C program to do the following:

// a) Insertion of keys in BST.
// b) Search a key in BST.
// c) Delete a Key from BST.
// d) Inorder traversal of BST to print BST.
// e) print height of BST.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the BST
struct Node
{
    int key;
    struct Node *left, *right;
};

// Function prototypes
struct Node *CreatenewNode(int key);
struct Node *insert(struct Node *root, int key);
struct Node *search(struct Node *root, int key);
struct Node *deleteNode(struct Node *root, int key);
void inorderTraversal(struct Node *root);
int getHeight(struct Node *root);

int main()
{
    struct Node *root = NULL;
    int choice, key;
    printf("*** BST Operations Menu ***\n\n");
    printf("1. Insertion of Keys in BST.\n");
    printf("2. Search a Key in BST.\n");
    printf("3. Delete a Key in BST.\n");
    printf("4. Inorder Traversal of BST to print BST.\n");
    printf("5. Print Height of BST.\n\n");
    while (1)
    {
        printf("Enter your choice = ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            printf("Key %d inserted in BST.\n", key);
            break;

        case 2:
            printf("Enter key to search: ");
            scanf("%d", &key);
            if (search(root, key) != NULL)
                printf("Key %d found in BST.\n", key);
            else
                printf("Key %d not found in BST.\n", key);
            break;

        case 3:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            printf("Key %d deleted from BST.\n", key);
            break;

        case 4:
            printf("Inorder Traversal of BST: ");
            inorderTraversal(root);
            printf("\n");
            break;

        case 5:
            printf("Height of BST: %d\n", getHeight(root));
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
    }
    return 0;
}

// Function to create a Node to insert a key into BST
struct Node *CreatenewNode(int key)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// Function to insert a key into BST
struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
    {
        root = CreatenewNode(key);
        return root;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Function to search for a key in BST
struct Node *search(struct Node *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Function to delete a key from BST
struct Node *deleteNode(struct Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// Function to perform inorder traversal of BST
void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Function to compute the height of BST
int getHeight(struct Node *root)
{
    if (root == NULL)
        return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}