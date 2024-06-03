// Write a menu driven program to implement the following:
// a) Given an array of integers, build a heap
// b) Extract and remove the max element
// c) Display the heap as a tree.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure for Max Heap
typedef struct MaxHeap
{
    int *arrh;
    int size;
    int capacity;
} MaxHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

MaxHeap *createHeap(int capacity)
{
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arrh = (int *)malloc(capacity * sizeof(int));
    return heap;
}

void heapifyDown(MaxHeap *heap, int i)
{
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < heap->size && heap->arrh[leftChild] > heap->arrh[largest])
        largest = leftChild;

    if (rightChild < heap->size && heap->arrh[rightChild] > heap->arrh[largest])
        largest = rightChild;

    if (largest != i)
    {
        swap(&heap->arrh[i], &heap->arrh[largest]);
        heapifyDown(heap, largest);
    }
}

void buildHeap(MaxHeap *heap, int *arr, int n)
{
    heap->size = n;
    for (int i = 0; i < n; i++)
    {
        heap->arrh[i] = arr[i];
    }

    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapifyDown(heap, i);
    }
}

int extractMax(MaxHeap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty\n");
        return -1;
    }

    int maxElement = heap->arrh[0];
    heap->arrh[0] = heap->arrh[heap->size - 1];
    heap->size--;

    heapifyDown(heap, 0);

    return maxElement;
}

void printTreeUtil(int *arr, int size, int Array[], int idx, int m, int n, int row, int col, int height)
{
    if (idx >= size)
        return;
    *((arr + row * n) + col) = Array[idx];
    printTreeUtil(arr, size, Array, 2 * idx + 1, m, n, row + 1, col - pow(2, height - 2), height - 1);
    printTreeUtil(arr, size, Array, 2 * idx + 2, m, n, row + 1, col + pow(2, height - 2), height - 1);
}

void printTree(int Array[], int size)
{
    int height = log(size) / log(2) + 1;
    int col = pow(2, height) - 1;
    int array[height][col];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < col; j++)
        {
            array[i][j] = 0;
        }
    }
    printTreeUtil((int *)array, size, Array, 0, height, col, 0, col / 2, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (array[i][j] == 0)
            {
                printf("   ");
            }
            else
            {
                printf("%3d", array[i][j]);
            }
        }
        printf("\n");
        printf("\n");
    }
}

int main()
{
    MaxHeap *heap;
    int choice, n, arr[100];
    printf("*** HEAP D.S. MENU PROGRAM ***\n\n\n");
label:
    printf("Enter the Number of Elements: ");
    scanf("%d", &n);
    printf("Enter the Elements: \n");
    printf("NOTE: Element cannot be 0(Zero).\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter Element-%d = ", i + 1);
        scanf("%d", &arr[i]);
    }
    heap = createHeap(n);
    buildHeap(heap, arr, n);
    printf("Heap built successfully.\n");
    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Extract and Remove Max Element.\n");
        printf("2. Display Heap as Tree.\n");
        printf("3. Add Elements Again.\n");
        printf("4. Exit\n");

        printf("Enter your choice (1/2/3/4): ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            if (heap->size > 0)
            {
                printf("Extracted Max Element: %d\n", extractMax(heap));
            }
            else
            {
                printf("Heap is Empty !!!\n");
            }
            break;

        case 2:
            if (heap->size > 0)
            {
                printf("Heap as Tree:\n");
                printTree(heap->arrh, heap->size);
            }
            else
            {
                printf("Heap is Empty !!!\n");
            }
            break;

        case 3:
            goto label;
            break;
        case 4:
            printf("Exiting program.\n");
            free(heap->arrh);
            free(heap);
            exit(0);

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
