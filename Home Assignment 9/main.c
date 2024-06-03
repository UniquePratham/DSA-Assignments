// Implement hash table with chaining by generating n =1000, 5000, 10000, 25000, 50000 keys. Let the universe U of keys be the maximum size of "long int" . Use appropriate m value. In chaining, insert the node at last.
// Count the number of nodes traversed during each insertion of key values.
// 1) Find the average of count over all n insertions.
// 2) Find the maximum length of any chain.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Function to generate Random Number in a given range irrespective of RAND_MAX
int custom_random(int lower, int upper)
{
    int random_num;
    if ((upper - lower + 1) > RAND_MAX || UINT_MAX == 0)
    {
        // Calculate the range size
        unsigned int range_size = (unsigned int)(upper - lower + 1);

        if (range_size == 0)
        {
            // Range size is too large, so set random_num to the lower value
            random_num = lower;
        }
        else
        {
            // Use multiple calls to rand() to generate a random number within the range
            random_num = 0;
            for (int i = 0; i < sizeof(random_num); i++)
            {
                random_num = (random_num << CHAR_BIT) | rand();
            }
            random_num %= range_size;
            random_num += lower;
        }
    }
    else
    {
        random_num = (rand() % (upper - lower + 1)) + lower;
    }

    return random_num;
}

// Node structure for chaining
struct Node {
    long int key;
    struct Node* next;
};

// Hash table structure
struct HashTable {
    int size;
    struct Node** table;
};

// Function to initialize a hash table with chaining
struct HashTable* initializeHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->table = (struct Node**)malloc(sizeof(struct Node*) * size);

    // Initialize each slot to NULL
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

// Function to insert a key into the hash table with chaining
void insert(struct HashTable* hashTable, long int key, int* count) {
    int index = key % hashTable->size;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;

    // Traverse the chain and insert the node at the last
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        struct Node* current = hashTable->table[index];
        while (current->next != NULL) {
            current = current->next;
            (*count)++;
        }
        current->next = newNode;
    }
}

int main() {
    int n;
    printf("Enter the number of keys (n): ");
    scanf("%d", &n);

    // Initialize hash table with an appropriate size (e.g., 2 times n)
    int m = 2 * n;
    struct HashTable* hashTable = initializeHashTable(m);

    int totalNodesTraversed = 0;
    int maxLengthOfChain = 0;

    // Insert n random keys into the hash table
    for (int i = 0; i < n; i++) {
        long int key = custom_random(0, LONG_MAX);
        int count = 1; // Initialize count for this insertion
        insert(hashTable, key, &count);
        totalNodesTraversed += count;

        // Update maximum length of any chain
        if (count > maxLengthOfChain) {
            maxLengthOfChain = count;
        }
    }

    // Calculate average number of nodes traversed during each insertion
    double averageNodesTraversed = (double)totalNodesTraversed / n;

    printf("Average number of nodes traversed: %.2lf\n", averageNodesTraversed);
    printf("Maximum length of any chain: %d\n", maxLengthOfChain);

    return 0;
}
