# Student.-C#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[50];
    float m1, m2, m3;
    float total;
};

// Function to add student
void addStudent() {
    struct student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter marks of 3 subjects: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    s.total = s.m1 + s.m2 + s.m3;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record added successfully!\n");
}

// Function to display students
void displayStudents() {
    struct student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Total: %.2f\n",
               s.roll, s.name, s.total);
    }

    fclose(fp);
}

// Function to generate rank list
void rankList() {
    struct student s[100];
    int i = 0, j;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    // Read all records
    while (fread(&s[i], sizeof(struct student), 1, fp)) {
        i++;
    }
    fclose(fp);

    // Sort (Descending order)
    for (int x = 0; x < i - 1; x++) {
        for (int y = x + 1; y < i; y++) {
            if (s[x].total < s[y].total) {
                struct student temp = s[x];
                s[x] = s[y];
                s[y] = temp;
            }
        }
    }

    // Display rank list
    printf("\n--- Rank List ---\n");
    for (j = 0; j < i; j++) {
        printf("Rank %d: %s (Roll %d) - Total: %.2f\n",
               j + 1, s[j].name, s[j].roll, s[j].total);
    }
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Generate Rank List\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankList(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
