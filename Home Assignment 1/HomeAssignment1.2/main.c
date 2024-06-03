/* 1.2 Given two big integers a and b of length m and n, multiply them and print their results (Use dynamic
memory allocations to create arrays). Note that, big integers can not be stored even in long int. You need to
create an array of m characters to store a m digit integer. You have to write the code the way you did your
multiplication in primary school, i.e, multiply, shift, add. Ex: 1234567 x 1111 is done as follows
            1234567
               1111
            -------
            1234567
           1234567
          1234567
         1234567
       -------------
         1371603937
*/

// Including Header Files
#include <stdio.h>  // For Input Output
#include <string.h> // For String
#include <stdlib.h> // For Dynamic Memory Allocation
#include <math.h>   // For Math Library

// Function to print character 'Y', 'X' times
void printXtimetheY(int x, char y)
{
    for (int p = 1; p <= x; p++)
    {
        printf("%c", y);
    }
}

// Function to make a Calculation History
void RecordtheCalculation(const char *a, const char *b, long long int result)
{
    char outputFilename[30];
    snprintf(outputFilename, sizeof(outputFilename), "Calculation_History.txt");
    FILE *file = fopen(outputFilename, "a");
    if (file == NULL)
    {
        printf("Unable to create the output file.\n");
        exit(1);
    }
    fprintf(file, "%s X %s = %lld\n", a, b, result);
}

// Function to multiply two big integers represented as strings and multiply them and print them.
void multiplyBigIntegersandprintthem(const char *a, const char *b)
{
    printf("\nThe Multiplication of %s and %s :\n\n", a, b);
    int m = strlen(a);
    int n = strlen(b);
    int *result = (int *)calloc(m + n, sizeof(int));

    // Array and Structure to store products
    struct productCont
    {
        int productArray[m + n];
    };
    struct productConts
    {
        struct productCont productArrays[n];
    };

    // Initialize the structure
    struct productConts products;

    // Initialize the initialSpacing variable
    int initialSpacing = n - 1 + 5;

    // Initialize multiplicationCarry and additionCarry
    int multiplicationCarry = 0;
    int *additionCarry = (int *)calloc(m + n, sizeof(int));

    // Print the multiplication format
    printf("\n");
    printXtimetheY(initialSpacing, ' ');
    printf("%s\n", a);
    printXtimetheY(initialSpacing - n - 1 + m, ' ');
    printf("x%s\n", b);
    printXtimetheY(initialSpacing, ' ');
    printXtimetheY(m, '-');
    printf("\n");

    // Multiplication Logic
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            // To print the last number as it is without doing it a carry
            if (j != 0)
            {
                // Add '0' to the character to make it integer and perform calculations
                int product = (a[j] - '0') * (b[i] - '0') + multiplicationCarry;
                multiplicationCarry = product / 10;

                // Store the product in the array
                products.productArrays[i].productArray[j + 1] = product % 10;
            }
            else
            {
                int product = (a[j] - '0') * (b[i] - '0') + multiplicationCarry;
                multiplicationCarry = 0;
                // Store the product in the structure
                products.productArrays[i].productArray[j + 1] = product % 10;
                products.productArrays[i].productArray[j] = product / 10;
            }
        }

        // Print the products digit by digit in reverse order
        if (products.productArrays[i].productArray[0] != 0 && i != 0)
        {
            printXtimetheY(initialSpacing - 1, ' ');
            for (int j = 0; j <= m; j++)
            {
                printf("%c", products.productArrays[i].productArray[j] + '0');
            }
        }
        else if (products.productArrays[i].productArray[0] == 0 && i != 0)
        {
            printXtimetheY(initialSpacing, ' ');
            for (int j = 1; j <= m; j++)
            {
                printf("%c", products.productArrays[i].productArray[j] + '0');
            }
        }
        else if (i == 0 && products.productArrays[i].productArray[0] != 0)
        {
            printXtimetheY(initialSpacing - 2, ' ');
            printf("+");
            for (int j = 0; j <= m; j++)
            {
                printf("%c", products.productArrays[i].productArray[j] + '0');
            }
        }
        else if (i == 0 && products.productArrays[i].productArray[0] == 0)
        {
            printXtimetheY(initialSpacing - 1, ' ');
            printf("+");
            for (int j = 1; j <= m; j++)
            {
                printf("%c", products.productArrays[i].productArray[j] + '0');
            }
        }

        printf("\n");
        initialSpacing--;
    }
    // Iterate through the stored products and perform the final addition
    int count = 0;
    for (int i = 0; i <= (m + n - 1); i++)
    {
        additionCarry[i] = 0;
        result[i] = 0;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m; j >= 0; j--)
        {
            int sum = products.productArrays[i].productArray[j] + additionCarry[m - j + count] + result[m - j + count];
            additionCarry[m - j + count] = 0;
            if (sum < 10)
            {
                result[m - j + count] = sum;
                additionCarry[m - j + count + 1] = 0;
            }
            else
            {
                result[m - j + count] = sum % 10;
                additionCarry[m - j + count + 1] = sum / 10;
            }
        }
        count++;
    }

    // Extra Decorations
    printXtimetheY(initialSpacing, ' ');
    printXtimetheY(m + n + initialSpacing - 5, '-');
    printf("\n");

    // Calculate the correct length for the result
    int len = m + n;
    while (len > 0 && result[len - 1] == 0)
    {
        len--;
    }
    if (((initialSpacing - 1) + 1 + len) == (m + n + 5))
    {
        printXtimetheY(initialSpacing - 1, ' ');
    }
    else
    {
        printXtimetheY(initialSpacing, ' ');
    }

    printf("=");
    long long int finalResult = 0;
    // Print the result
    for (int i = len - 1; i >= 0; i--)
    {
        printf("%d", result[i]);
        finalResult += (result[i] * pow(10, i));
    }

    printf("\n\n");
    // Free memory for the result array
    RecordtheCalculation(a, b, finalResult);
    free(additionCarry);
    free(result);
}

int main()
{
    // Initializing lengths
    int m, n;

    printf("Enter the length of the first number: ");
    scanf("%d", &m);

    printf("Enter the length of the second number: ");
    scanf("%d", &n);

    // Check for invalid length input
    if (m <= 0 || n <= 0)
    {
        printf("Invalid input. Lengths must be positive integers.\n");
        return 1; // Exit with an error code
    }

    char *a = (char *)malloc((m + 1) * sizeof(char)); // +1 for null terminator
    char *b = (char *)malloc((n + 1) * sizeof(char));

    // Check whether allocation is successful or not
    if (a == NULL || b == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    // Take the big integer as input in character array
    printf("Enter the first number: ");
    scanf("%s", a);

    printf("Enter the second number: ");
    scanf("%s", b);

    // Check if the lengths of a and b match the specified lengths
    if (strlen(a) != m || strlen(b) != n)
    {
        printf("Lengths of entered numbers do not match the specified lengths.\n");
        free(a);
        free(b);
        return 1; // Exit with an error code
    }

    // Compare the lengths of a and b and swap if necessary; Making a the bigger one always
    if (strlen(a) < strlen(b))
    {
        char *temp = a;
        a = b;
        b = temp;
    }

    multiplyBigIntegersandprintthem(a, b);

    free(a);
    free(b);
    return 0;
}
