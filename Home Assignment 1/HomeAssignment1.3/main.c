/* Create an attendance file ”attendance.txt” that contains roll numbers, names and attendances of all students
on different dates. Given your attendance file, store the information of the student in appropriate structure to
compute the following: (Write a menu driven program.)
   • print % of attendance of each student till a particular date and store the results in a file.
   • print the details of the student who has the highest percentage of attendance till a particular date.
   • print the total number of classes taken by the teacher
   • print the details of the student who has the lowest percentage of attendance till a particular date.
   • print the mean percentage of attendance till a particular date.
   • ..... (if you can extract any other information from attendance)
 */
// ASSUMPTIONS - Taking input a CSV File with custom header as roll number, name and custom dates then taking attendance as 0 or 1 where 0 - means absent and 1 means present
// Including Header Files
#include <stdio.h>     // For Input Output
#include <string.h>    // For String
#include <stdlib.h>    // For Dynamic Memory Allocation
#include <ctype.h>     // For Characters Operations
#include <sys/stat.h>  // For MKDIR
#include <sys/types.h> // For MKDIR

#define MAX_STUDENTS 50         // Maximum number of students
#define MAX_DATES 50            // Maximum number of dates
#define MAX_NAME_LENGTH 50      // Maximum length of a name
#define MAX_FILENAME_LENGTH 100 // Maximum length of a filename
#define MAX_HEADER_LENGTH 1000  // Maximum length of a header

// Defining Structures
struct Student
{
    char rollNumber[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    int attendance[MAX_DATES];
    int totalClassesAttended;
};

struct AttendanceData
{
    char rollNumber[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    double attendancePercentage;
};

// Function to Extract Integer from Mixed String
int extractIntFromMixedString(const char *charArray)
{
    int result = 0;
    int sign = 1; // Positive by default

    // Check for a minus sign at the beginning
    if (*charArray == '-')
    {
        sign = -1;
        charArray++; // Move past the minus sign
    }

    // Skip non-digit characters
    while (*charArray && !isdigit(*charArray))
    {
        charArray++;
    }

    // Extract the integer part
    while (*charArray && isdigit(*charArray))
    {
        result = result * 10 + (*charArray - '0');
        charArray++;
    }

    return result * sign;
}

// Function to Load the Attendance Data into the Structure when File is provided
void loadAttendanceData(struct Student students[], int *numStudents, int *numDates, char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found or unable to open.\n");
        exit(1);
    }

    char header[MAX_HEADER_LENGTH];
    if (fgets(header, sizeof(header), file) == NULL)
    {
        printf("Error reading the header line.\n");
        exit(1);
    }

    *numStudents = 0;
    *numDates = 0;

    while (*numStudents < MAX_STUDENTS &&
           (fscanf(file, "\n%[^,],%[^,],", students[*numStudents].rollNumber, students[*numStudents].name) == 2))
    {
        students[*numStudents].totalClassesAttended = 0;

        for (*numDates = 0; *numDates < MAX_DATES; (*numDates)++)
        {
            if (fscanf(file, "%d,", &students[*numStudents].attendance[*numDates]) != 1)
            {
                break;
            }
        }
        for (int i = 0; i < *numDates; i++)
        {
            if (students[*numStudents].attendance[i] == 1)
            {
                students[*numStudents].totalClassesAttended++;
            }
        }
        (*numStudents)++;
    }

    fclose(file);
}

// Function to Calculate Attendance Percentage according till Date
struct AttendanceData *calculateAttendancePercentage(struct Student students[], int numStudents, int numDates, const char date[])
{
    struct AttendanceData *data = (struct AttendanceData *)malloc(numStudents * sizeof(struct AttendanceData));

    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    int currentRequiredDate;
    int len = strlen(date);
    if (len == 3 && strcmp(date, "all") == 0)
    {
        currentRequiredDate = numDates;
    }
    else if (len > 4 && len < 7)
    {
        currentRequiredDate = extractIntFromMixedString(date);
    }
    else
    {
        printf("Invalid Date Input.\n");
        exit(1);
    }
    for (int i = 0; i < numStudents; i++)
    {
        int attendedClasses = 0;
        if (currentRequiredDate == numDates)
        {
            attendedClasses = students[i].totalClassesAttended;
        }
        else
        {
            for (int j = 0; j < currentRequiredDate; j++)
            {
                if (students[i].attendance[j] == 1)
                {
                    attendedClasses++;
                }
            }
        }
        if (attendedClasses == 0)
        {
            data[i].attendancePercentage = 0.0;
        }
        else
        {
            data[i].attendancePercentage = (double)attendedClasses / currentRequiredDate * 100;
        }
        strncpy(data[i].rollNumber, students[i].rollNumber, MAX_NAME_LENGTH);
        strncpy(data[i].name, students[i].name, MAX_NAME_LENGTH);
    }

    return data;
}

// Function to print Attendance Data of All Students according to till Date and also Save it in a File if User wants
void printAttendanceData(struct AttendanceData *data, int numStudents, char date[], char content[])
{
    char check[5];
    printf("\nDo you also want to make an Output File of the Information (Yes/No/Y/N) ?: ");
    scanf("%s", check);
    const char *folder_name = "OutputFiles";
    if ((strcmp(check, "yes") == 0) || (strcmp(check, "Yes") == 0) || (strcmp(check, "Y") == 0) || (strcmp(check, "y") == 0))
    {
        // Create a new folder
        mkdir(folder_name);
        char outputFilename[MAX_FILENAME_LENGTH];
        snprintf(outputFilename, sizeof(outputFilename), "%s/%s_%s.txt", folder_name, content, date);
        FILE *file = fopen(outputFilename, "w");
        if (file == NULL)
        {
            printf("Unable to create the output file.\n");
            exit(1);
        }
        fprintf(file, "%s of Students till %s\n\n", content, date);
        for (int i = 0; i < numStudents; i++)
        {
            printf("Roll: %s, Name: %s --> Attendance %% till %s: %.2f%%\n", data[i].rollNumber, data[i].name, date, data[i].attendancePercentage);
            fprintf(file, "Roll: %s, Name: %s --> Attendance %% till %s: %.2f%%\n", data[i].rollNumber, data[i].name, date, data[i].attendancePercentage);
        }
        fclose(file);
        printf("\n\nOutput File Created Successfully !!!\n");
    }

    else if ((strcmp(check, "No") == 0) || (strcmp(check, "no") == 0) || (strcmp(check, "N") == 0) || (strcmp(check, "n") == 0))
    {
        for (int i = 0; i < numStudents; i++)
        {
            printf("Roll: %s, Name: %s --> Attendance %% till %s: %.2f%%\n", data[i].rollNumber, data[i].name, date, data[i].attendancePercentage);
        }
    }
    else
    {
        printf("Invalid Answer !!!");
    }
}

// Function to print Single Student Attendance Data according to till Date
void printSingleStudentAttendanceData(struct AttendanceData temp, int numStudents, char date[])
{
    printf("\nRoll: %s, Name: %s --> Attendance %% till %s: %.2f%%\n", temp.rollNumber, temp.name, date, temp.attendancePercentage);
}
// Function to check the Student structure basically for debugging purpose
void printStudentInfo(struct Student students[], int numStudents, int numDates)
{
    for (int i = 0; i < numStudents; i++)
    {
        printf("Roll: %s, Name: %s, Total Classes Attended: %d, Attendance: ", students[i].rollNumber, students[i].name, students[i].totalClassesAttended);
        for (int j = 0; j < numDates; j++)
        {
            if (j == 0)
            {
                printf("%d", students[i].attendance[j]);
            }
            else if (j == (numDates - 1))
            {
                printf(",%d\n", students[i].attendance[j]);
            }
            else
            {
                printf(",%d", students[i].attendance[j]);
            }
        }
    }
}

// Function to Display the Menu of the Attendance Management System
void displayMenuFunction(struct Student students[], int numStudents, int numDates)
{
    int choice;
    char date[MAX_NAME_LENGTH];
    while (1)
    {
        printf("\n***** Attendance Management Menu: *****\n");
        printf("1. Calculate %% of Attendance for Each Student till a Particular Date\n");
        printf("2. Find the Student with the Highest Attendance %% till a Particular Date\n");
        printf("3. Find the student with the Lowest Attendance %% till a Particular Date\n");
        printf("4. Calculate the Mean Attendance %% till a Particular Date\n");
        printf("5. Print the Total Number of Classes Taken\n");
        printf("6. Print the Total Number of Students in the Classes\n");
        printf("7. Print the Sorted List of Students\n");
        printf("8. Search Student by Name or Roll Number \n");
        printf("9. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        struct AttendanceData *data = NULL;

        switch (choice)
        {
        case 1: // To Display the Attendance Percentage of All Students according to till Date
            printf("Enter the date (e.g., 'Date1'): ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);
            printf("\n");
            printAttendanceData(data, numStudents, date, "Attendance_Percentage");
            free(data);
            break;

        case 2: // To Display the Highest Attendance Percentage Student
            printf("Enter the date (e.g., 'Date1'): ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);

            int highestIndex = 0;
            double highestPercentage = data[0].attendancePercentage;

            for (int i = 1; i < numStudents; i++)
            {
                if (data[i].attendancePercentage > highestPercentage)
                {
                    highestIndex = i;
                    highestPercentage = data[i].attendancePercentage;
                }
            }
            struct AttendanceData temp3;
            temp3 = data[highestIndex];
            printf("\nStudent with the Highest Attendance Percentage till %s:\n", date);
            printSingleStudentAttendanceData(temp3, numStudents, date);
            free(data);
            break;

        case 3: // To Display the Lowest Attendance Percentage Student
            printf("Enter the date (e.g., 'Date1'): ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);

            int lowestIndex = 0;
            double lowestPercentage = data[0].attendancePercentage;

            for (int i = 1; i < numStudents; i++)
            {
                if (data[i].attendancePercentage < lowestPercentage)
                {
                    lowestIndex = i;
                    lowestPercentage = data[i].attendancePercentage;
                }
            }

            struct AttendanceData temp4;
            temp4 = data[lowestIndex];
            printf("\nStudent with the Lowest Attendance Percentage till %s:\n", date);
            printSingleStudentAttendanceData(temp4, numStudents, date);
            free(data);
            break;

        case 4: // To Display the Mean Attendance Percentage out of All Students
            printf("Enter the date (e.g., 'Date1') or 'all' for all dates: ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);
            double totalAttendancePercentage = 0;
            for (int i = 0; i < numStudents; i++)
            {
                totalAttendancePercentage += data[i].attendancePercentage;
            }
            double meanAttendancePercentage = totalAttendancePercentage / numStudents;
            printf("Mean Percentage of Attendance till %s: %.2f\n", date, meanAttendancePercentage);
            free(data);
            break;

        case 5: // To Display the Total Number of Classes
            printf("Total Number of Classes Taken: %d\n", numDates);
            break;

        case 6: // To Display the Total Number of Students in the Classes
            printf("Total Number of Students in the Classes: %d\n", numStudents);
            break;

        case 7: // To Display the Attendance Percentage of All the Students in Sorted Order
            printf("Enter the date (e.g., 'Date1') or 'all' for all dates: ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);
            int choice;
            printf("\n\nChoose the Method for Sorting :\n");
            printf("1. Ascending Order!\n");
            printf("2. Descending Order!\n");

            printf("\nEnter Your Choice: ");
            scanf("%d", &choice);
            struct AttendanceData temp;
            switch (choice)
            {
            case 1:
                for (int i = 0; i < numStudents; ++i)
                {
                    for (int j = i + 1; j < numStudents; j++)
                    {
                        if (data[i].attendancePercentage > data[j].attendancePercentage)
                        {
                            temp = data[i];
                            data[i] = data[j];
                            data[j] = temp;
                        }
                    }
                }
                printf("\nStudents Attendance Record in Ascending Order:\n");
                printAttendanceData(data, numStudents, date, "Ascending_Order_Attendance_Percentage");
                break;
            case 2:
                for (int i = 0; i < numStudents; ++i)
                {
                    for (int j = i + 1; j < numStudents; j++)
                    {
                        if (data[i].attendancePercentage < data[j].attendancePercentage)
                        {
                            temp = data[i];
                            data[i] = data[j];
                            data[j] = temp;
                        }
                    }
                }
                printf("\nStudents Attendance Record in Descending Order:\n");
                printAttendanceData(data, numStudents, date, "Descending_Order_Attendance_Percentage");
                break;

            default:
                printf("\nInvalid choice. Please select a valid option.\n");
            }
            break;

        case 8: // To Search Student by Name or Roll Number
            printf("Enter the date (e.g., 'Date1') or 'all' for all dates: ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);
            char searchChar[MAX_NAME_LENGTH];
            printf("\nEnter Student's Full Name or Roll Number: ");
            // Read the full line of input
            getchar(); // Consume the newline character left from the previous input
            fgets(searchChar, sizeof(searchChar), stdin);

            // Remove the trailing newline character
            size_t len = strlen(searchChar);
            if (searchChar[len - 1] == '\n')
            {
                searchChar[len - 1] = '\0';
            }
            int bool = 0;
            struct AttendanceData temp2;
            for (int i = 0; i < numStudents; i++)
            {
                if ((strcmp(searchChar, data[i].name)) == 0 || (strcmp(searchChar, data[i].rollNumber)) == 0)
                {
                    temp2 = data[i];
                    bool = 1;
                    break;
                }
            }
            if (bool == 1)
            {
                printSingleStudentAttendanceData(temp2, numStudents, date);
            }
            else
            {
                printf("\nInvalid Data, No Results Found !!!\n");
            }
            break;
        case 9:
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("\nInvalid choice. Please select a valid option.\n");
        }
    }
};

int main()
{
    // Defining Variables and Structures
    char filename[MAX_FILENAME_LENGTH];
    int choice;
    int attendancePercentageOrder[MAX_STUDENTS];
    int numStudents, numDates;
    struct Student students[MAX_STUDENTS];

    // Taking File as input
    printf("*_*_*_*_* ATTENDANCE MANAGEMENT SYSTEM: *_*_*_*_*\n\n");
    printf("Choose the File for the Attendance Management System\n");
    printf("1. Manually Enter the FileName!\n");
    printf("2. Take the Default Filename as 'attendance.txt'\n");
    printf("\nEnter Your Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Manually Take Input a File
        printf("\nEnter the Filename you want to check in Attendance System. ");
        // printf("Press any character and Enter if filename is attendance.txt");
        scanf("%s", filename);

        loadAttendanceData(students, &numStudents, &numDates, filename); // Reading File
        displayMenuFunction(students, numStudents, numDates);            // Display Menu
        // printStudentInfo(students, numStudents, numDates); // For Debugging
        break;

    case 2: // Select "attendance.txt" File as Default
        strncpy(filename, "attendance.txt", MAX_FILENAME_LENGTH);
        filename[MAX_FILENAME_LENGTH - 1] = '\0'; // Ensure null-termination

        loadAttendanceData(students, &numStudents, &numDates, filename); // Reading File
        displayMenuFunction(students, numStudents, numDates);            // Display Menu
        // printStudentInfo(students, numStudents, numDates); // For Debugging
        break;
    default:
        printf("\nInvalid choice. Please select a valid option.\n");
    }

    return 0;
}
