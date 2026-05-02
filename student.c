#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float m1, m2, m3, total;
};

void addStudent() {
    FILE *fp = fopen("students.txt", "a");
    struct Student s;

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

void displayStudents() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s;

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Total: %.2f\n",
               s.roll, s.name, s.total);
    }

    fclose(fp);
}

void rankList() {
    FILE *fp = fopen("students.txt", "r");
    struct Student s[100];
    int n = 0, i, j;

    while (fread(&s[n], sizeof(struct Student), 1, fp)) {
        n++;
    }
    fclose(fp);

    // Sorting (Descending order)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i].total < s[j].total) {
                struct Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (i = 0; i < n; i++) {
        printf("Rank %d: %s (Total: %.2f)\n",
               i + 1, s[i].name, s[i].total);
    }
}

int main() {
    int choice;

    do {
        printf("\n1. Add Student\n2. Display\n3. Rank List\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankList(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice\n");
        }

    } while (choice != 4);

    return 0;
}
