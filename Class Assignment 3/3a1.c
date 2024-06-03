/* 3.a) F(n) = F(n-1) + F(n-2), for all n > 1
        F(0) = 0 and F(1) = 1
1.) Write an iterative program to print the nth term in the Fibonacci sequence for a given input n. */
#include <stdio.h>
int fiboIterfn(int n)
{
    if (n <= 1)
        return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
int main()
{
    int n;
    printf("Enter the number to print the nth term in the Fibonacci sequence = ");
    scanf("%d", &n);
    int result = fiboIterfn(n);
    printf("\n F(%d) = %d\n", n, result);
    return 0;
}
