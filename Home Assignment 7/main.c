// Write a menu driven program to insert and delete keys in an AVL tree. There must be an option to print the tree as follows:
// 1) by inorder traversal
// 2) as we draw binary trees on paper.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int Height(struct Node *node)
{
    if (!node)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int balance_factor(struct Node *node)
{
    if (!node)
        return 0;
    return Height(node->left) - Height(node->right);
}

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *RightRotate(struct Node *temp)
{
    struct Node *temp1 = temp->left;
    temp->left = temp1->right;
    temp1->right = temp;

    temp->height = max(Height(temp->left), Height(temp->right)) + 1;
    temp1->height = max(Height(temp1->left), Height(temp1->right)) + 1;

    return temp1;
}

struct Node *LeftRotate(struct Node *temp)
{
    struct Node *temp1 = temp->right;
    temp->right = temp1->left;
    temp1->left = temp;

    temp->height = max(Height(temp->left), Height(temp->right)) + 1;
    temp1->height = max(Height(temp1->left), Height(temp1->right)) + 1;

    return temp1;
}

struct Node *insertkey(struct Node *root, int data)
{
    if (!root)
        return newNode(data);

    if (data < root->key)
        root->left = insertkey(root->left, data);
    else if (data > root->key)
        root->right = insertkey(root->right, data);
    else
        return root;

    root->height = max(Height(root->left), Height(root->right)) + 1;

    int balance = balance_factor(root);

    if (balance > 1 && data < root->left->key)
        return RightRotate(root);
    if (balance < -1 && data > root->right->key)
        return LeftRotate(root);
    if (balance > 1 && data > root->left->key)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    if (balance < -1 && data < root->right->key)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}

struct Node *successor(struct Node *root)
{
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

struct Node *deletekey(struct Node *root, int data)
{
    if (!root)
        return root;

    if (data < root->key)
    {
        root->left = deletekey(root->left, data);
    }
    else if (data > root->key)
    {
        root->right = deletekey(root->right, data);
    }
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            struct Node *temp = successor(root->right);
            root->key = temp->key;
            root->right = deletekey(root->right, temp->key);
        }
    }

    if (!root)
        return root;

    root->height = max(Height(root->left), Height(root->right)) + 1;

    int balance = balance_factor(root);

    if (balance > 1 && balance_factor(root->left) >= 0)
        return RightRotate(root);
    if (balance > 1 && balance_factor(root->left) < 0)
    {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    if (balance < -1 && balance_factor(root->right) <= 0)
        return LeftRotate(root);
    if (balance < -1 && balance_factor(root->right) > 0)
    {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}

void Inorder_Traversal(struct Node *root)
{
    if (root)
    {
        Inorder_Traversal(root->left);
        printf("%d ", root->key);
        Inorder_Traversal(root->right);
    }
}

void printTreeUtil(int *arr, struct Node *root, int m, int n, int row, int col, int height)
{
    if (!root)
        return;
    *((arr + row * n) + col) = root->key;
    printTreeUtil(arr, root->left, m, n, row + 1, col - pow(2, height - 2), height - 1);
    printTreeUtil(arr, root->right, m, n, row + 1, col + pow(2, height - 2), height - 1);
}

void printTree(struct Node *root)
{
    int height = Height(root) + 1;
    int col = pow(2, height) - 1;
    int array[height][col];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = 0;
        }
    }
    printTreeUtil((int *)array, root, height, col, 0, col / 2, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (array[i][j] == 0)
            {
                printf(" ");
            }
            else
            {
                printf("%d", array[i][j]);
            }
        }
        printf("\n");
        printf("\n");
    }
}

int main()
{
    struct Node *root = NULL;
    int choice, value;
    printf("*** AVL Tree MENU Program ***\n\n\n 1.Insert Multiple Keys.\n 2.Insert a Single Key.\n 3.Delete a Key.\n 4.Display in In-Order Traversal.\n 5.Draw and Display AVL Tree.\n 6.Exit \n\n");
    while (1)
    {
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Number of Keys: ");
            int key;
            scanf("%d", &key);
            for (int i = 0; i < key; i++)
            {
                printf("Enter Key-%d : ", i + 1);
                scanf("%d", &value);
                root = insertkey(root, value);
                printf("Insertion Successful \n");
            }
            printf("%d Keys Successfully Inserted.\n", key);
            break;

        case 2:
            printf("Enter Key Value to be Inserted: ");
            scanf("%d", &value);
            root = insertkey(root, value);
            printf("Insertion Successful \n");
            break;

        case 3:
            printf("Enter Key Value to be Deleted: ");
            scanf("%d", &value);
            root = deletekey(root, value);
            printf("Deletion Successful \n");
            break;

        case 4:
            printf("The In-Order Traversal of Given Tree is: ");
            Inorder_Traversal(root);
            printf("\n");
            break;

        case 5:
            printf("The Given Tree is as follows:\n");
            printTree(root);
            break;

        case 6:
            printf("Thanks for using AVL Tree. \n\n");
            exit(1);
        default:
            printf("Invalid Choice, Please Try Again !!!\n");
        }
    }
}