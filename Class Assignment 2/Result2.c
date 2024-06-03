#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_RECORDS 100

struct Student
{
    int rank;
    int roll;
    char *name;
    int marks;
};

int compareList(const void *a, const void *b)
{
    return ((struct Student *)b)->marks - ((struct Student *)a)->marks;
}

int main()
{
    FILE *fpr;
    fpr = fopen("student.txt", "r");
    int stdRecord = 0;
    fscanf(fpr, "%d", &stdRecord);
    printf("stdRecord=%d\n", stdRecord);

    if (fpr == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    struct Student *students = (struct Student *)malloc(MAX_RECORDS * sizeof(struct Student));

    for (int i = 0; i < stdRecord; ++i)
    {
        students[i].name = (char *)malloc(MAX_NAME_LENGTH);
        fscanf(fpr, "%d %s %d", &students[i].roll, students[i].name, &students[i].marks);
    }

    fclose(fpr);

    qsort(students, stdRecord, sizeof(struct Student), compareList);

    fpr = fopen("new_Student.txt", "w");

    if (fpr == NULL)
    {
        perror("Error opening fpr for writing");
        return 1;
    }

    fprintf(fpr, "%d\n", stdRecord);

    for (int i = 0; i < stdRecord; ++i)
    {
        students[i].rank = i;
        fprintf(fpr, "%d %d %s\t %d\n", students[i].rank + 1, students[i].roll, students[i].name, students[i].marks);
    }

    printf("Displaying Information in increasing order with their ranks:\n");
    for (int i = 0; i < stdRecord; ++i)
    {
        printf("%d\t%d\t%s\t\t%d\n", students[i].rank + 1, students[i].roll, students[i].name, students[i].marks);
        free(students[i].name);
    }

    free(students);
    fclose(fpr);

    printf("File successfully sorted and updated with both rank and serial number.\n");

    return 0;
}
