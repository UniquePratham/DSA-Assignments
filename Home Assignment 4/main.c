// Write a menu driven ( see below) program to implement addition, subtraction, multiplications of two polynomial expression that uses  circular singly linked list. The node stores the coefficient, exponent pair of the polynomial expression. they must always be in decreasing order of the exponent in the circular singly linked list. You must use the "Avail" singly linked list for new nodes in the polynomial and return a node from polynomial to "Avail" list whenever a node is deleted from a polynomial due to add, subtract, multiply operations.
// at the end of the program, you must free the "Avail" list.
// The menu is as follows:
// 1. Create a polynomial
// 2. Add polynomial (A, B)
// 3. Subtract polynomial (A, B)
// 4. Multiply polynomial (A, B)
// 5. Display polynomial (A)
// 6. Display Avail List
// 7. Exit

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in the polynomial
struct Term
{
    int coeff;
    int exp;
    struct Term *next;
};

// Structure to represent a polynomial
struct Polynomial
{
    struct Term *head;
};

// Structure to represent a node in the "Avail" list
struct AvailNode
{
    struct Term *term;
    struct AvailNode *next;
};

// Function to create a new term with given coefficient and exponent
struct Term *createTerm(int coeff, int exp)
{
    struct Term *newTerm = (struct Term *)malloc(sizeof(struct Term));
    if (newTerm == NULL)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newTerm->coeff = coeff;
    newTerm->exp = exp;
    newTerm->next = NULL;

    return newTerm;
}

// Function to create a new AvailNode with given term
struct AvailNode *createAvailNode(struct Term *term)
{
    struct AvailNode *newNode = (struct AvailNode *)malloc(sizeof(struct AvailNode));
    if (newNode == NULL)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->term = term;
    newNode->next = NULL;

    return newNode;
}

// Function to insert a term into a polynomial in decreasing order of exponent
void insertTerm(struct Polynomial *poly, struct Term *newTerm)
{
    struct Term *current = poly->head;
    struct Term *prev = NULL;

    while (current != NULL && current->exp > newTerm->exp)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        newTerm->next = poly->head;
        poly->head = newTerm;
    }
    else
    {
        prev->next = newTerm;
        newTerm->next = current;
    }
}

// Function to display a polynomial
void displayPolynomial(struct Polynomial *poly)
{
    struct Term *current = poly->head;

    while (current != NULL)
    {
        if (current->exp != 1)
        {
            printf("(%dx^%d)", current->coeff, current->exp);
        }
        else
        {
            printf("(%dx)", current->coeff);
        }
        current = current->next;
        if (current != NULL)
        {
            printf(" + ");
        }
    }
    printf("\n\n");
}

// Function to add two polynomials and return the result
struct Polynomial *addPolynomials(struct Polynomial *polyA, struct Polynomial *polyB)
{
    struct Polynomial *result = (struct Polynomial *)malloc(sizeof(struct Polynomial));
    result->head = NULL;

    struct Term *termA = polyA->head;
    struct Term *termB = polyB->head;

    while (termA != NULL && termB != NULL)
    {
        if (termA->exp > termB->exp)
        {
            insertTerm(result, createTerm(termA->coeff, termA->exp));
            termA = termA->next;
        }
        else if (termA->exp < termB->exp)
        {
            insertTerm(result, createTerm(termB->coeff, termB->exp));
            termB = termB->next;
        }
        else
        {
            int sumCoeff = termA->coeff + termB->coeff;
            if (sumCoeff != 0)
            {
                insertTerm(result, createTerm(sumCoeff, termA->exp));
            }
            termA = termA->next;
            termB = termB->next;
        }
    }

    // Add any remaining terms from polyA
    while (termA != NULL)
    {
        insertTerm(result, createTerm(termA->coeff, termA->exp));
        termA = termA->next;
    }

    // Add any remaining terms from polyB
    while (termB != NULL)
    {
        insertTerm(result, createTerm(termB->coeff, termB->exp));
        termB = termB->next;
    }

    return result;
}

// Function to subtract polynomial B from A and return the result
struct Polynomial *subtractPolynomials(struct Polynomial *polyA, struct Polynomial *polyB)
{
    struct Polynomial *result = (struct Polynomial *)malloc(sizeof(struct Polynomial));
    result->head = NULL;

    struct Term *termA = polyA->head;
    struct Term *termB = polyB->head;

    while (termA != NULL && termB != NULL)
    {
        if (termA->exp > termB->exp)
        {
            insertTerm(result, createTerm(termA->coeff, termA->exp));
            termA = termA->next;
        }
        else if (termA->exp < termB->exp)
        {
            insertTerm(result, createTerm(-termB->coeff, termB->exp));
            termB = termB->next;
        }
        else
        {
            int diffCoeff = termA->coeff - termB->coeff;
            if (diffCoeff != 0)
            {
                insertTerm(result, createTerm(diffCoeff, termA->exp));
            }
            termA = termA->next;
            termB = termB->next;
        }
    }

    // Add any remaining terms from polyA
    while (termA != NULL)
    {
        insertTerm(result, createTerm(termA->coeff, termA->exp));
        termA = termA->next;
    }

    // Subtract any remaining terms from polyB
    while (termB != NULL)
    {
        insertTerm(result, createTerm(-termB->coeff, termB->exp));
        termB = termB->next;
    }

    return result;
}

// Function to multiply two polynomials and return the result
struct Polynomial *multiplyPolynomials(struct Polynomial *polyA, struct Polynomial *polyB)
{
    struct Polynomial *result = (struct Polynomial *)malloc(sizeof(struct Polynomial));
    result->head = NULL;

    struct Term *termA = polyA->head;

    while (termA != NULL)
    {
        struct Term *termB = polyB->head;

        while (termB != NULL)
        {
            int productCoeff = termA->coeff * termB->coeff;
            int productExp = termA->exp + termB->exp;

            struct Term *productTerm = createTerm(productCoeff, productExp);
            insertTerm(result, productTerm);

            termB = termB->next;
        }

        termA = termA->next;
    }

    return result;
}

// Function to display the "Avail" list
void displayAvailList(struct AvailNode *availList)
{
    printf("Avail List: ");
    struct AvailNode *current = availList;

    while (current != NULL)
    {
        printf("(%dx^%d)", current->term->coeff, current->term->exp);
        current = current->next;
        if (current != NULL)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Function to free the memory allocated for the "Avail" list
void freeAvailList(struct AvailNode *availList)
{
    while (availList != NULL)
    {
        struct AvailNode *temp = availList;
        availList = availList->next;
        free(temp->term);
        free(temp);
    }
}

// Function to delete a term from a polynomial and add it to the "Avail" list
void deleteTerm(struct Polynomial *poly, struct AvailNode **availList, int exp)
{
    struct Term *current = poly->head;
    struct Term *prev = NULL;

    while (current != NULL && current->exp != exp)
    {
        prev = current;
        current = current->next;
    }

    if (current != NULL)
    {
        if (prev == NULL)
        {
            poly->head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        // Add the deleted term to the "Avail" list
        struct AvailNode *availNode = createAvailNode(current);
        availNode->next = *availList;
        *availList = availNode;
    }
}

// Function to create a polynomial using user input
struct Polynomial *createPolynomial()
{
    struct Polynomial *poly = (struct Polynomial *)malloc(sizeof(struct Polynomial));
    poly->head = NULL;

    int n, coeff, exp;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter the coefficient of term %d: ", i + 1);
        scanf("%d", &coeff);
        printf("Enter the exponent of term %d: ", i + 1);
        scanf("%d", &exp);
        insertTerm(poly, createTerm(coeff, exp));
    }

    return poly;
}

int main()
{
    struct Polynomial *polyA = NULL;
    struct Polynomial *polyB = NULL;
    struct AvailNode *availList = NULL;

    int choice, ch;
    do
    {
        printf("*** Polynomial Expression Evaluator ***\n\n");
        printf("1. Create polynomial\n");
        printf("2. Add polynomials (A, B)\n");
        printf("3. Subtract polynomials (A, B)\n");
        printf("4. Multiply polynomials (A, B)\n");
        printf("5. Display polynomial (A,B)\n");
        printf("6. Display Avail List\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nCreate Polynomial:\n");
            printf("Enter the polynomial label (A or B): ");
            char label;
            scanf(" %c", &label);
            if (label == 'A' || label == 'a')
            {
                if (polyA != NULL)
                {
                    freeAvailList(availList);
                    free(polyA);
                }
                polyA = createPolynomial();
            }
            else if (label == 'B' || label == 'b')
            {
                if (polyB != NULL)
                {
                    freeAvailList(availList);
                    free(polyB);
                }
                polyB = createPolynomial();
            }
            else
            {
                printf("Invalid polynomial label\n");
            }
            break;

        case 2:
            if (polyA != NULL && polyB != NULL)
            {
                struct Polynomial *sum = addPolynomials(polyA, polyB);
                displayPolynomial(sum);
                freeAvailList(availList);
                free(polyA);
                free(polyB);
                free(sum);
                polyA = NULL;
                polyB = NULL;
            }
            else if (polyA != NULL && polyB == NULL)
            {
                printf("Polynomials B must be created first to do operation with Polynomial A\n\n");
            }
            else if (polyA == NULL && polyB != NULL)
            {
                printf("Polynomials A must be created first to do operation with Polynomial B\n\n");
            }
            else
            {
                printf("Polynomials A and B must be created first\n\n");
            }
            break;

        case 3:
            if (polyA != NULL && polyB != NULL)
            {
                struct Polynomial *diff = subtractPolynomials(polyA, polyB);
                displayPolynomial(diff);
                freeAvailList(availList);
                free(polyA);
                free(polyB);
                free(diff);
                polyA = NULL;
                polyB = NULL;
            }
            else if (polyA != NULL && polyB == NULL)
            {
                printf("Polynomials B must be created first to do operation with Polynomial A\n\n");
            }
            else if (polyA == NULL && polyB != NULL)
            {
                printf("Polynomials A must be created first to do operation with Polynomial B\n\n");
            }
            else
            {
                printf("Polynomials A and B must be created first\n\n");
            }
            break;

        case 4:
            if (polyA != NULL && polyB != NULL)
            {
                struct Polynomial *product = multiplyPolynomials(polyA, polyB);
                displayPolynomial(product);
                freeAvailList(availList);
                free(polyA);
                free(polyB);
                free(product);
                polyA = NULL;
                polyB = NULL;
            }
            else if (polyA != NULL && polyB == NULL)
            {
                printf("Polynomials B must be created first to do operation with Polynomial A\n\n");
            }
            else if (polyA == NULL && polyB != NULL)
            {
                printf("Polynomials A must be created first to do operation with Polynomial B\n\n");
            }
            else
            {
                printf("Polynomials A and B must be created first\n\n");
            }
            break;

        case 5:
            printf("Which polynomial do you want to print\n");
            printf("1. Polynomial A\n");
            printf("2. Polynomial B\n\n");
            printf("Enter your choice: ");
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
                if (polyA != NULL)
                {
                    displayPolynomial(polyA);
                }
                else
                {
                    printf("Polynomial A must be created first\n\n");
                }
                break;
            case 2:
                if (polyB != NULL)
                {
                    displayPolynomial(polyB);
                }
                else
                {
                    printf("Polynomial B must be created first\n\n");
                }
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
            break;

        case 6:
            if (availList != NULL)
            {
                displayAvailList(availList);
            }
            else
            {
                printf("AvailList is empty !!!\n\n");
            }
            break;

        case 7:
            freeAvailList(availList);
            free(polyA);
            free(polyB);
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }
    } while (choice != 7);

    return 0;
}
