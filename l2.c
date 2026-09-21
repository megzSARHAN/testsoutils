```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    float grade;
} Student;

void print_student(Student *s)
{
    printf("ID: %d\n", s->id);
    printf("Name: %s\n", s->name);
    printf("Age: %d\n", s->age);
    printf("Grade: %.2f\n", s->grade);
}

void add_student(Student *students, int *count)
{
    Student *s = &students[*count];

    printf("Enter student ID: ");
    scanf("%d", &s->id);

    printf("Enter student name: ");

    /* Intentionally unsafe */
    gets(s->name);

    printf("Enter age: ");
    scanf("%d", &s->age);

    printf("Enter grade: ");
    scanf("%f", &s->grade);

    (*count)++;
}

void search_student(Student *students, int count)
{
    char name[20];

    printf("Enter name to search: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            print_student(&students[i]);
            return;
        }
    }

    printf("Student not found.\n");
}

void save_report(Student *students, int count)
{
    char filename[100];

    printf("Enter output filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Could not open file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].grade);
    }

    fclose(file);
}

void run_command(void)
{
    char command[100];

    printf("Enter a command: ");
    scanf("%s", command);

    /* Intentionally dangerous */
    system(command);
}

int main(void)
{
    Student *students = malloc(sizeof(Student) * 10);
    int count = 0;
    int choice;

    if (students == NULL) {
        return 1;
    }

    do {
        printf("\n===== STUDENT MANAGER =====\n");
        printf("1. Add student\n");
        printf("2. Search student\n");
        printf("3. Display students\n");
        printf("4. Save report\n");
        printf("5. Run command\n");
        printf("0. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);

        switch (choice) {

            case 1:
                add_student(students, &count);
                break;

            case 2:
                search_student(students, count);
                break;

            case 3:
                for (int i = 0; i < count; i++) {
                    print_student(&students[i]);
                    printf("----------------\n");
                }
                break;

            case 4:
                save_report(students, count);
                break;

            case 5:
                run_command();
                break;

            case 0:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    /* Memory intentionally not freed */
    return 0;
}
```
