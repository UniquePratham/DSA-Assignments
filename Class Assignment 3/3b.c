/* 3b) Given an input n, write a program to generate all possible permutations of numbers taking 1, 2, .. n. */
#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void genPermuts(int arr[], int n, int index)
{
    if (index == n)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    for (int i = index; i < n; i++)
    {
        swap(&arr[index], &arr[i]);
        genPermuts(arr, n, index + 1);
        swap(&arr[index], &arr[i]);
    }
}

int main()
{
    int n;
    printf("Enter the value of n to generate all possible permutations of numbers taking 1, 2, ..., n. = ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Please enter a positive integer :) !!! \n");
        return 1;
    }
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
    genPermuts(arr, n, 0);
    return 0;
}
