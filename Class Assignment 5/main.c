/* 4 : Write a C program implementing Merge sort. Run the program with  same  set of random numbers as in Bubble sort. Count the number of comparisons in each case.
 */

// Including Header Files
#include <stdio.h>     // For Input Output
#include <stdlib.h>    // For File Handling
#include <time.h>      // For Random Number
#include <string.h>    // For String
#include <stdbool.h>   // For Boolean Values
#include <sys/stat.h>  // For MKDIR
#include <sys/types.h> // For MKDIR

// Declaration of Functions
long long merge(int arr[], int l, int m, int r);
long long mergeSort(int arr[], int l, int r);
int custom_random(int a, int b);
bool filesExistthenDel(const char *folder_name, int setSize, int run);
int main()
{
    srand(time(0)); // Seed the random number generator with current time

    // Variables
    int num;
    const char *folder_name = "RandNumTextFiles";
    struct sizeDetail
    {
        int set_size;
        long long run[10];
    };

    // Taking the specific number of elements 'n' as input
    printf("Enter the number 'n' to generate 'n' Random Numbers = ");
    scanf("%d", &num);

    // Deleting already created files if any
    for (int i = 1; i <= 10; i++)
    {
        if (filesExistthenDel(folder_name, num, i))
        {
            printf("\nFile with same set size '%d' and run '%d' already exists. So, File deleted successfully\n", num, i);
        }
    }

    // Create a new folder
    mkdir(folder_name);
    // Essential Variables
    int num_runs = 10;
    struct sizeDetail size_details;

    long long total_comparisons = 0;
    long long average_comparisons = 0;
    int setSize = num;
    size_details.set_size = setSize;
    int random_numbers[setSize];
    printf("\n\nFor set Size - %d, Random Numbers from the range [-%d,%d] :\n\n", setSize, setSize, setSize);
    for (int run = 1; run <= num_runs; run++)
    {
        int a = -setSize;
        int b = setSize;
        // Generate and store random numbers in the array, including both positive and negative numbers in range from -n to n
        for (int j = 0; j < setSize; j++)
        {
            random_numbers[j] = custom_random(a, b);
        }

        // Create the full file path including the folder, set size, and run number
        char filename[100];
        snprintf(filename, sizeof(filename), "%s/random_numbers_%d_run%d.txt", folder_name, setSize, run);

        // Open the file for writing
        FILE *file = fopen(filename, "a");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        fprintf(file, "Run %d for setSize - %d \n\n", run, setSize);
        fprintf(file, "Random Numbers List from range -%d to %d : \n\n", setSize, setSize);
        fprintf(file, "Unsorted Random Numbers: ");
        for (int j = 0; j < setSize; j++)
        {
            fprintf(file, "%d ", random_numbers[j]);
        }
        // Sort the array using Merge Sort and count comparisons
        long long comparisons = mergeSort(random_numbers, 0, setSize);
        // Write the sorted numbers back to the file
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        fprintf(file, "\n\nSorted Random Numbers: ");
        for (int j = 0; j < setSize; j++)
        {
            fprintf(file, "%d ", random_numbers[j]);
        }
        fprintf(file, "\n\nNumber of Comparisons for this run = %lld", comparisons);
        fclose(file);

        // Display the number of comparisons per run and storing it to find the average
        printf("Run %d: Comparisons = %lld\n", run, comparisons);
        size_details.run[run] = comparisons;
    }
    // Calculate the total comparisons and then average comparisons after 10 runs of a setSize
    for (int k = 1; k <= 10; k++)
    {
        total_comparisons += size_details.run[k];
    }

    average_comparisons = total_comparisons / 10;
    // Display the average comparisons per setSize
    printf("\nAverage Comparisons for size %d from 10 runs = %lld\n\n", setSize, average_comparisons);

    return 0;
}

// Function to merge two subarrays and count comparisons
long long merge(int arr[], int l, int m, int r)
{
    long long comparisons = 0;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    // Merge the two subarrays back into the original array arr[]
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
        comparisons++; // Counting the number of comparisons
    }
    // Copy the remaining elements of L[] and R[] if any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
    return comparisons;
}

// Function to perform merge sort and count comparisons
long long mergeSort(int arr[], int l, int r)
{
    long long comparisons = 0;
    if (l < r)
    {
        int m = l + (r - l) / 2;
        // Recursively sort the first and second halves and count comparisons
        comparisons += mergeSort(arr, l, m);
        comparisons += mergeSort(arr, m + 1, r);

        // Merge the sorted halves and count comparisons
        comparisons += merge(arr, l, m, r);
    }
    return comparisons;
}

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

bool filesExistthenDel(const char *folder_name, int setSize, int run)
{
    char filename[100];
    snprintf(filename, sizeof(filename), "%s/random_numbers_%d_run%d.txt", folder_name, setSize, run);
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        int ret = remove(filename);
        if (ret == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
}
