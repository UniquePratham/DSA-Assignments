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
#include <ctype.h>     // Include the ctype.h header for isdigit
#include <sys/stat.h>  // For MKDIR
#include <sys/types.h> // For MKDIR

#define MAX_STUDENTS 50
#define MAX_DATES 50
#define MAX_NAME_LENGTH 50
#define MAX_FILENAME_LENGTH 100
#define MAX_HEADER_LENGTH 1000

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

void incrementRollNumber(struct Student *student)
{
    int rollNumberInt;
    if (sscanf(student->rollNumber, "Roll%d", &rollNumberInt) == 1)
    {
        snprintf(student->rollNumber, sizeof(student->rollNumber), "Roll%03d", rollNumberInt + 1);
    }
}
void decrementRollNumber(struct Student *student)
{
    int rollNumberInt;
    if (sscanf(student->rollNumber, "Roll%d", &rollNumberInt) == 1)
    {
        snprintf(student->rollNumber, sizeof(student->rollNumber), "Roll%03d", rollNumberInt - 1);
    }
}

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

void saveAttendanceDataToFile(struct Student students[], int numStudents, int numDates, char filename[])
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening the file for writing.\n");
        return;
    }

    // Write the header
    fprintf(file, "RollNumber,Name");
    for (int i = 0; i < numDates; i++)
    {
        fprintf(file, ",Date%d", i + 1);
    }
    fprintf(file, "\n");

    // Write student data
    for (int i = 0; i < numStudents; i++)
    {
        fprintf(file, "%s,%s", students[i].rollNumber, students[i].name);
        for (int j = 0; j < numDates; j++)
        {
            fprintf(file, ",%d", students[i].attendance[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Changes saved to %s.\n", filename);
}

void addStudentAtIndex(struct Student students[], int *numStudents, int numDates, int index)
{
    if (*numStudents >= MAX_STUDENTS)
    {
        printf("Max student limit reached. Cannot add more students.\n");
        return;
    }

    if (index + 1 < 0 || index > *numStudents + 1)
    {
        printf("Invalid index for adding a student.\n");
        return;
    }

    struct Student newStudent;
    printf("Enter Roll Number: ");
    getchar(); // Consume the newline character left from the previous input
    fgets(newStudent.rollNumber, sizeof(newStudent.rollNumber), stdin);

    printf("Enter Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    // Remove the trailing newline character
    size_t len = strlen(newStudent.rollNumber);
    if (newStudent.rollNumber[len - 1] == '\n')
    {
        newStudent.rollNumber[len - 1] = '\0';
    }
    len = strlen(newStudent.name);
    if (newStudent.name[len - 1] == '\n')
    {
        newStudent.name[len - 1] = '\0';
    }
    printf("\nEnter Attendance (0 or 1) for each date:\n");
    for (int i = 0; i < numDates; i++)
    {
        printf("Attendance for Date%d: ", i + 1);
        scanf("%d", &newStudent.attendance[i]);
        if (newStudent.attendance[i] == 0 || newStudent.attendance[i] == 1)
        {
            if (newStudent.attendance[i] == 1)
            {
                newStudent.totalClassesAttended++;
            }
        }
        else
        {
            printf("\nInvalid Entry ! Student Addition Failed!!!\n");
            return;
        }
    }

    // Shift existing students to create space for the new student
    if (index < *numStudents)
    {
        for (int i = *numStudents; i > index; i--)
        {
            students[i] = students[i - 1];
            incrementRollNumber(&students[i]);
        }
    }
    (*numStudents)++;
    students[index] = newStudent;
    printf("Student added successfully.\n");
}

void deleteStudentByRollOrName(struct Student students[], int *numStudents, int numDates, char rollOrName[])
{
    int found = 0;
    for (int i = 0; i < *numStudents; i++)
    {
        if (strcmp(rollOrName, students[i].rollNumber) == 0 || strcmp(rollOrName, students[i].name) == 0)
        {
            // Found the student and delete it
            for (int j = i; j < *numStudents; j++)
            {
                students[j] = students[j + 1];
                decrementRollNumber(&students[j]);
            }
            (*numStudents)--;
            found = 1;
            printf("Student deleted successfully.\n");
            break;
        }
    }
    if (!found)
    {
        printf("Student not found.\n");
    }
}
void deleteStudentByIndex(struct Student students[], int *numStudents, int numDates, int index)
{
    if (index > -1 && index < *numStudents)
    {
        // Found the student and delete it
        for (int i = index; i < *numStudents; i++)
        {
            students[i] = students[i + 1];
            decrementRollNumber(&students[i]);
        }
        (*numStudents)--;
        printf("Student deleted successfully.\n");
    }
    else
    {
        printf("Student not found.\n");
    }
}
// Function that does the students info update process
void updateProcess(struct Student students[], int numStudents, int numDates, int index)
{
    char check[5];
    printf("\nDo you want to update Name (Yes/No) for %s = ", students[index].rollNumber);
    scanf("%s", check);
    int len;
    if ((strcmp(check, "yes") == 0) || (strcmp(check, "Yes") == 0) || (strcmp(check, "Y") == 0) || (strcmp(check, "y") == 0))
    {
        printf("Enter Name: ");
        getchar(); // Consume the newline character left from the previous input
        fgets(students[index].name, sizeof(students[index].name), stdin);
        // Remove the trailing newline character
        len = strlen(students[index].name);
        if (students[index].name[len - 1] == '\n')
        {
            students[index].name[len - 1] = '\0';
        }
    }
    else if ((strcmp(check, "No") == 0) || (strcmp(check, "no") == 0) || (strcmp(check, "N") == 0) || (strcmp(check, "n") == 0))
    {
        goto TIER;
    }
    else
    {
        printf("Invalid Input !!!");
        return;
    }
TIER:
    printf("Enter new attendance (0 or 1) for each date:\n");
    for (int i = 0; i < numDates; i++)
    {
        printf("Attendance for Date%d: ", i + 1);
        scanf("%d", &students[index].attendance[i]);
        if (students[index].attendance[i] == 0 || students[index].attendance[i] == 1)
        {
            if (students[index].attendance[i] == 1)
            {
                students[index].totalClassesAttended++;
            }
        }
        else
        {
            printf("\nInvalid Entry ! Student Updation Failed!!!\n");
            return;
        }
    }
    printf("Student record updated successfully.\n");
}

// Function to update Student Information by Roll Number
void updateStudentByRoll(struct Student students[], int numStudents, int numDates, char rollNumber[])
{
    int found = 0;
    int index = extractIntFromMixedString(rollNumber);
    index--;
    int len = strlen(rollNumber);
    if ((len == 1 || len == 2) && index > 0 && index < numStudents)
    {
        updateProcess(students, numStudents, numDates, index);
        found = 1;
    }
    else if (len == 7)
    {
        for (int i = 0; i < numStudents; i++)
        {
            if (strcmp(rollNumber, students[i].rollNumber) == 0)
            {

                updateProcess(students, numStudents, numDates, i);
                found = 1;
                break;
            }
        }
    }
    else
    {
        printf("\nInvalid Entry! Or ");
    }
    if (!found)
    {
        printf("Student not found.\n");
    }
}

// Function to add dates for all students
void addDatesForStudents(struct Student students[], int *numStudents, int *numDates, int numDatesToAdd)
{
    if (*numDates + numDatesToAdd > MAX_DATES)
    {
        printf("Maximum number of dates reached. Cannot add more dates.\n");
        return;
    }

    // Update the attendance data for all students
    for (int i = 0; i < *numStudents; i++)
    {
        for (int j = *numDates; j <= (*numDates + numDatesToAdd - 1); j++)
        {
            students[i].attendance[j] = -1; // Initialize the new dates as empty (use -1 for unmarked)
        }
    }

    *numDates += numDatesToAdd;
    printf("Dates added successfully.\n");
}

// Function to modify Student Attendance for Specific Date Range
#include <stdio.h>
#include <string.h>

// ...

// Function to update attendance for a particular student within a date range
void updateAttendanceForStudent(struct Student students[], int numStudents, int numDates)
{
    char rollOrName[MAX_NAME_LENGTH];
    char start_date_str[MAX_NAME_LENGTH];
    char end_date_str[MAX_NAME_LENGTH];
    int start_date, end_date;

    printf("Enter the Student's Name or Roll Number: ");
    getchar(); // Consume the newline character left from the previous input
    fgets(rollOrName, sizeof(rollOrName), stdin);

    size_t len = strlen(rollOrName);
    if (rollOrName[len - 1] == '\n')
    {
        rollOrName[len - 1] = '\0';
    }

    int student_index = -1;
    for (int i = 0; i < numStudents; i++)
    {
        if (strcmp(rollOrName, students[i].rollNumber) == 0 || strcmp(rollOrName, students[i].name) == 0)
        {
            student_index = i;
            break;
        }
    }

    if (student_index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    printf("Enter the Start Date (e.g., 'Date1'): ");
    scanf("%s", start_date_str);

    start_date = extractIntFromMixedString(start_date_str);

    if (start_date <= 0 || start_date >= numDates)
    {
        printf("Invalid Start Date.\n");
        return;
    }

    printf("Enter the End Date (e.g., 'Date1'): ");
    scanf("%s", end_date_str);

    end_date = extractIntFromMixedString(end_date_str);

    if (end_date <= 0 || end_date > numDates || end_date <= start_date)
    {
        printf("Invalid End Date.\n");
        return;
    }

    printf("Enter Attendance (0 or 1) for the Specified Date Range:\n");
    for (int i = start_date - 1; i <= end_date - 1; i++)
    {
        printf("Attendance for Date%d for %s: ", i + 1, students[student_index].name);
        scanf("%d", &students[student_index].attendance[i]);
    }

    // Update the totalClassesAttended for the student
    students[student_index].totalClassesAttended = 0;
    for (int i = 0; i < numDates; i++)
    {
        if (students[student_index].attendance[i] == 1)
        {
            students[student_index].totalClassesAttended++;
        }
    }

    printf("Attendance for %s for a Date Range of %s to %s updated successfully.\n", students[student_index].name, start_date_str, end_date_str);
}

// Function to delete dates for all students
void deleteDatesForStudents(struct Student students[], int *numStudents, int *numDates, int numDatesToDelete)
{
    if (*numDates - numDatesToDelete < 0)
    {
        printf("The number of dates can't be negative. Unable to delete dates.\n");
        return;
    }

    // Update the attendance data for all students
    for (int i = 0; i < *numStudents; i++)
    {
        for (int j = *numDates - 1; j >= *numDates - numDatesToDelete; j--)
        {
            students[i].attendance[j] = 0; // Delete the data for the last 'numDatesToDelete' dates
        }
    }

    *numDates -= numDatesToDelete;
    printf("Dates deleted successfully.\n");
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

void displayMenuFunction(struct Student students[], int numStudents, int numDates, char filename[])
{
    int choice;
    char date[MAX_NAME_LENGTH];
    while (1)
    {
        printf("\n***** Attendance Management Menu: *****.\n");
        printf("1. Calculate %% of Attendance for Each Student till a Particular Date.\n");
        printf("2. Find the Student with the Highest Attendance %% till a Particular Date.\n");
        printf("3. Find the student with the Lowest Attendance %% till a Particular Date.\n");
        printf("4. Calculate the Mean Attendance %% till a Particular Date.\n");
        printf("5. Print the Total Number of Classes Taken.\n");
        printf("6. Print the Total Number of Students in the Classes.\n");
        printf("7. Print the Sorted List of Students.\n");
        printf("8. Search Student by Name or Roll Number .\n");
        printf("9. Add a Student's Info.\n");
        printf("10. Delete a Student's Info.\n");
        printf("11. Update a Student's Info.\n");
        printf("12. Add Dates for Students Attendance.\n");
        printf("13. Delete Dates for Students Attendance.\n");
        printf("14. Modify Student Attendance Data for a Specific Date Range.\n");
        printf("15. Exit.\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        struct AttendanceData *data = NULL;
        char rollOrName[MAX_NAME_LENGTH];
        char rollNumber[MAX_NAME_LENGTH];
        int Index;

        switch (choice)
        {
        case 1:
            printf("Enter the date (e.g., 'Date1'): ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);
            printf("\n");
            printAttendanceData(data, numStudents, date, "Attendance_Percentage");
            free(data);
            break;

        case 2:
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

        case 3:
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

        case 4:
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

        case 5:
            printf("Total Number of Classes Taken: %d\n", numDates);
            break;

        case 6:
            printf("Total Number of Students in the Classes: %d\n", numStudents);
            break;

        case 7:
            printf("Enter the date (e.g., 'Date1') or 'all' for all dates: ");
            scanf("%s", date);
            data = calculateAttendancePercentage(students, numStudents, numDates, date);
            int sortChoice;
            printf("\n\nChoose the Method for Sorting :\n");
            printf("1. Ascending Order!\n");
            printf("2. Descending Order!\n");

            printf("\nEnter Your Choice: ");
            scanf("%d", &sortChoice);
            struct AttendanceData temp;
            switch (sortChoice)
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

        case 8:
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

        case 9: // Add student
            printf("Enter the position to add the student: ");
            scanf("%d", &Index);
            Index--;
            addStudentAtIndex(students, &numStudents, numDates, Index);
            saveAttendanceDataToFile(students, numStudents, numDates, filename);
            break;

        case 10: // Delete student
            printf("\n\nChoose the Method for Deletion :\n");
            printf("1. Delete by Position!!!\n");
            printf("2. Delete by Name or Roll Number!!!\n");
            printf("\nEnter Your Choice: ");
            int delChoice;
            scanf("%d", &delChoice);
            switch (delChoice)
            {
            case 1:
                printf("Enter the position to add the student: ");
                scanf("%d", &Index);
                Index--;
                deleteStudentByIndex(students, &numStudents, numDates, Index);
                break;

            case 2:
                printf("Enter Roll Number or Name of the student to delete: ");
                // Read the full line of input
                getchar(); // Consume the newline character left from the previous input
                fgets(rollOrName, sizeof(rollOrName), stdin);
                size_t len = strlen(rollOrName);
                if (rollOrName[len - 1] == '\n')
                {
                    rollOrName[len - 1] = '\0';
                }
                deleteStudentByRollOrName(students, &numStudents, numDates, rollOrName);
                break;

            default:
                printf("\nInvalid choice. Please select a valid option.\n");
                break;
            }

            saveAttendanceDataToFile(students, numStudents, numDates, filename);
            break;

        case 11: // Update student
            printf("Enter Roll Number of the student to update (Roll0XX): ");
            getchar(); // Consume the newline character left from the previous input
            fgets(rollNumber, sizeof(rollNumber), stdin);
            len = strlen(rollNumber);
            if (rollNumber[len - 1] == '\n')
            {
                rollNumber[len - 1] = '\0';
            }
            updateStudentByRoll(students, numStudents, numDates, rollNumber);
            saveAttendanceDataToFile(students, numStudents, numDates, filename);
            break;

        case 12: // Add dates for students
            printf("Enter the number of new dates to add: ");
            int numDatesToAdd;
            scanf("%d", &numDatesToAdd);
            addDatesForStudents(students, &numStudents, &numDates, numDatesToAdd);
            saveAttendanceDataToFile(students, numStudents, numDates, filename);
            break;

        case 13: // Delete dates for students
            printf("Enter the number of dates to delete: ");
            int numDatesToDelete;
            scanf("%d", &numDatesToDelete);
            deleteDatesForStudents(students, &numStudents, &numDates, numDatesToDelete);
            saveAttendanceDataToFile(students, numStudents, numDates, filename);
            break;

        case 14:
            printf("\nChange Attendance of a Student for a Date Range\n");
            updateAttendanceForStudent(students, numStudents, numDates);
            saveAttendanceDataToFile(students, numStudents, numDates, filename);
            break;

        case 15: // Exit Program
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("\nInvalid choice. Please select a valid option.\n");
        }
    }
};

int main()
{
    struct Student students[MAX_STUDENTS];
    int choice;
    int attendancePercentageOrder[MAX_STUDENTS];
    char filename[MAX_FILENAME_LENGTH];
    int numStudents, numDates;

    printf("*_*_*_*_* ATTENDANCE MANAGEMENT SYSTEM: *_*_*_*_*\n\n");
    printf("Choose the File for the Attendance Management System\n");
    printf("1. Manually Enter the FileName!\n");
    printf("2. Take the Default Filename as 'attendance.txt'\n");

    printf("\nEnter Your Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("\nEnter the Filename you want to check in Attendance System. ");
        // printf("Press any character and Enter if filename is attendance.txt");
        scanf("%s", filename);

        loadAttendanceData(students, &numStudents, &numDates, filename);
        displayMenuFunction(students, numStudents, numDates, filename);
        // printStudentInfo(students, numStudents, numDates);
        break;

    case 2:
        strncpy(filename, "attendance.txt", MAX_FILENAME_LENGTH);
        filename[MAX_FILENAME_LENGTH - 1] = '\0'; // Ensure null-termination

        loadAttendanceData(students, &numStudents, &numDates, filename);
        displayMenuFunction(students, numStudents, numDates, filename);
        // printStudentInfo(students, numStudents, numDates);
        break;
    default:
        printf("\nInvalid choice. Please select a valid option.\n");
    }

    return 0;
}
