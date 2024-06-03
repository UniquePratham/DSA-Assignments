/* Write a C program to display the given matrix into the spiral matrix.
Name- Pratham Agarwal Roll No - 407 Exam Roll - T91/CSE/224051
*/
#include <stdio.h>
int main()
{
    int m, n=0 , k = 1;
    // printf("Enter the the row of the matrix = ");
    // scanf("%d", &m);
    // printf("Enter the the column of the matrix = ");
    // scanf("%d", &n);
    // int arr[m][n];
    // int top = 0, bottom = n - 1, left = 0, right = m - 1;
    printf("Enter the the column of the matrix = ");
    scanf("%d", &n);
    int arr[n][n];
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    while (left <= right && top <= bottom)
    {
        // Traversing Left to Right
        for (int i = left; i <= right; i++)
        {
            arr[top][i] = k;
            k++;
        }
        top++;
        // Traversing Top to Bottom
        for (int i = top; i <= bottom; i++)
        {
            arr[i][right] = k;
            k++;
        }
        right--;
        // Traversing Right to Left
        for (int i = right; i >= left; i--)
        {
            arr[bottom][i] = k;
            k++;
        }
        bottom--;
        // Traversing Bottom to Top
        for (int i = bottom; i >= top; i--)
        {
            arr[i][left] = k;
            k++;
        }
        left++;
    }
    // Print the spiral matrix
    printf("Spiral Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
