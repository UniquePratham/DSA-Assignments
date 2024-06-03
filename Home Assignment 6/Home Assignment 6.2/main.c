// Generate 1000, 5000, 10000, 50000 and so on random numbers and consider them to be the inputs. Run your program  to insert those keys, compute the height of the tree in each case. Report the height and best case height of such number of keys.

// Run BST insertion for 10 sets of each of 1000, 5000, 10000, 50000 .... random  key values. Compute the average height of BST for each of  1000, 5000, 10000, 50000 keys and compare with best case heights.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the BST
struct Node
{
    int key;
    struct Node *left, *right;
};

// Function prototypes
struct Node *insert(struct Node *root, int key);
void generateRandomKeys(int n, int keys[]);
float runBSTInsertion(int keys[], int n);
float computeAverageHeight(int n, int sets, int keys[]);
int getHeight(struct Node *root);

int main()
{
    struct Node *root = NULL;
    int choice;

    printf("Enter the Number of Random Numbers you want to generate for BST = ");
    scanf("%d", &choice);

    int *inputKeys = (int *)malloc(choice * sizeof(int));

    // Generating random keys for different sets
    generateRandomKeys(choice, inputKeys);

    // Running BST insertion for each set and computing average height
    float avgHeightChoice = computeAverageHeight(choice, 10, inputKeys);
    printf("\nAverage Height for %d keys: %.2f\n", choice, avgHeightChoice);

    return 0;
}
// Function to generate random keys for a given set size
void generateRandomKeys(int n, int keys[])
{
    for (int i = 0; i < n; i++)
        keys[i] = rand();
}

// Function to run BST insertion for a set of keys and return the height
float runBSTInsertion(int keys[], int n)
{
    struct Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, keys[i]);

    return getHeight(root);
}

// Function to compute the average height of BST for a given set size and number of sets
float computeAverageHeight(int n, int sets, int keys[])
{
    float totalHeight = 0.0;
    for (int i = 0; i < sets; i++)
        totalHeight += runBSTInsertion(keys, n);

    return totalHeight / sets;
}

// Function to insert a key into BST
struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
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