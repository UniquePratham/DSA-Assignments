/* 3a)F(n) = F(n-1) + F(n-2), for all n > 1
F(0) = 0 and F(1) = 1
2) Write a recursive program to print the nth term in the Fibonacci sequence for a given input n. Let c(i) represents the number of times  F(i) is called in the recursion. Compute c(i) , for i = 1 to n,
Example:
                                                  F(5) :calls F(4) and F(3)
                                                   |
                      F(4) ----------------------------------------------------- F(3)
                       |                                                          |
           F(3)-----------------F(2)                                 F(2)-------------------F(1)
            |                    |                                    |                      |
      F(2)-----F(1)        F(1)----- F(0)                       F(1)----- F(0)              stop
       |        |           |         |                          |         |
F(1)----- F(0) stop        stop      stop                       stop      stop
 |         |
stop      stop

c (0) = 3, c(1) = 5, c(2)= 3, c(3) = 2, c(4) = 1, c(5) = 1 */
#include <stdio.h>
int fiboRecurfn(int n, int *c)
{
    if (n == 0)
    {
        c[0] += 1;
        return 0;
    }
    if (n == 1)
    {
        c[1] += 1;
        return 1;
    }
    c[n] += 1;
    return fiboRecurfn(n - 1, c) + fiboRecurfn(n - 2, c);
}
int main()
{
    int n;
    printf("Enter the number to print the nth term in the Fibonacci sequence = ");
    scanf("%d", &n);
    int c[n + 1];
    for (int i = 0; i <= n; i++)
    {
        c[i] = 0;
    }
    int result = fiboRecurfn(n, c);
    printf("\nF(%d) = %d\n", n, result);
    for (int i = 0; i <= n; i++)
    {
        printf("c(%d) = %d\n", i, c[i]);
    }
    return 0;
}