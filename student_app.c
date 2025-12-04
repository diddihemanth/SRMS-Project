#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

char currentUser[50];
char currentRole[20];

/* ---------- Utility: read masked password ---------- */
void read_password_masked(char *password, int maxLen) {
    int idx = 0;
    char ch;
    while (1) {
        ch = _getch();
        if (ch == 13) { /* Enter */
            password[idx] = '\0';
            putchar('\n');
            break;
        } else if (ch == 8) { /* Backspace */
            if (idx > 0) {
                idx--;
                printf("\b \b");
            }
        } else if (ch == 0 || ch == 224) { /* special keys */
            _getch();
        } else {
            if (idx < maxLen - 1) {
                password[idx++] = ch;
                putchar('*');
            }
        }
    }
}

/* ---------- Case-insensitive helpers ---------- */
void str_to_lower(const char *src, char *dst, int maxlen) {
    int i;
    for (i = 0; i < maxlen-1 && src[i] != '\0'; ++i)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

/* ---------- Login (3 attempts) ---------- */
int login_with_attempts() {
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];
    int attempts = 0;
    while (attempts < 3) {
        printf("USERNAME: ");
        if (scanf("%49s", inUser) != 1) return 0;
        getchar(); /* consume newline */

        printf("PASSWORD: ");
        read_password_masked(inPass, sizeof(inPass));

        FILE *fp = fopen(CRE_FILE, "r");
        if (!fp) {
            printf("Credential file missing! Please create %s in the program folder.\n", CRE_FILE);
            return 0;
        }

        int ok = 0;
        while (fscanf(fp, "%49s %49s %19s", u, p, r) == 3) {
            if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
                strcpy(currentUser, u);
                strcpy(currentRole, r);
                ok = 1;
                break;
            }
        }
        fclose(fp);

        if (ok) return 1;

        attempts++;
        if (attempts < 3)
            printf("Wrong username/password. Attempts left: %d\n", 3 - attempts);
        else
            printf("Too many failed attempts. Exiting.\n");
    }
    return 0;
}

/* ---------- Student operations ---------- */
void addStudent() {
    int roll;
    char name[100];
    float mark;

    printf("Roll: ");
    if (scanf("%d", &roll) != 1) { while(getchar()!='\n'); printf("Invalid roll.\n"); return; }
    printf("Name (no spaces): ");
    if (scanf("%99s", name) != 1) { printf("Invalid name.\n"); return; }
    printf("Mark: ");
    if (scanf("%f", &mark) != 1) { while(getchar()!='\n'); printf("Invalid mark.\n"); return; }

    FILE *fp = fopen(STUD_FILE, "a");
    if (!fp) { printf("Unable to open students file for writing.\n"); return; }
    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);
    printf("Student added!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file found (or empty).\n");
        return;
    }
    int roll;
    char name[100];
    float mark;
    printf("Roll\tName\tMark\n");
    printf("----\t----\t----\n");
    while (fscanf(fp, "%d %99s %f", &roll, name, &mark) == 3) {
        printf("%d\t%s\t%.2f\n", roll, name, mark);
    }
    fclose(fp);
}

/* ---------- Updated search: by roll OR by name ---------- */
void searchStudent() {
    int choice;
    printf("\nSearch Options:\n1. Search by Roll\n2. Search by Name\nChoice: ");
    if (scanf("%d", &choice) != 1) { while(getchar()!='\n'); printf("Invalid choice.\n"); return; }
    getchar(); /* consume newline */

    if (choice == 1) {
        int find;
        printf("Enter roll to search: ");
        if (scanf("%d", &find) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }

        FILE *fp = fopen(STUD_FILE, "r");
        if (!fp) { printf("No students file.\n"); return; }
        int roll;
        char name[100];
        float mark;
        int found = 0;
        while (fscanf(fp, "%d %99s %f", &roll, name, &mark) == 3) {
            if (roll == find) {
                printf("Found: Roll:%d Name:%s Mark:%.2f\n", roll, name, mark);
                found = 1;
                break;
            }
        }
        fclose(fp);
        if (!found) printf("Student not found!\n");
    }
    else if (choice == 2) {
        char qname[100];
        printf("Enter name (or part of name) to search: ");
        if (scanf("%99s", qname) != 1) { printf("Invalid input.\n"); return; }

        char qlower[100], namelower[100];
        str_to_lower(qname, qlower, sizeof(qlower));

        FILE *fp = fopen(STUD_FILE, "r");
        if (!fp) { printf("No students file.\n"); return; }
        int roll;
        char name[100];
        float mark;
        int found_any = 0;
        while (fscanf(fp, "%d %99s %f", &roll, name, &mark) == 3) {
            str_to_lower(name, namelower, sizeof(namelower));
            if (strstr(namelower, qlower) != NULL) {
                if (!found_any) {
                    printf("Matches found:\nRoll\tName\tMark\n----\t----\t----\n");
                }
                printf("%d\t%s\t%.2f\n", roll, name, mark);
                found_any = 1;
            }
        }
        fclose(fp);
        if (!found_any) printf("No student matches the name '%s'.\n", qname);
    }
    else {
        printf("Invalid choice.\n");
    }
}

void deleteStudent() {
    int delRoll;
    printf("Enter roll to delete: ");
    if (scanf("%d", &delRoll) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { printf("No students file.\n"); return; }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) { fclose(fp); printf("Unable to create temp file.\n"); return; }

    int roll;
    char name[100];
    float mark;
    int found = 0;
    while (fscanf(fp, "%d %99s %f", &roll, name, &mark) == 3) {
        if (roll != delRoll) {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student deleted!\n");
    else printf("Roll not found!\n");
}

void updateStudent() {
    int updateRoll;
    printf("Enter roll to update: ");
    if (scanf("%d", &updateRoll) != 1) { while(getchar()!='\n'); printf("Invalid input.\n"); return; }
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { printf("No students file.\n"); return; }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) { fclose(fp); printf("Unable to create temp file.\n"); return; }

    int roll;
    char name[100];
    float mark;
    int found = 0;
    while (fscanf(fp, "%d %99s %f", &roll, name, &mark) == 3) {
        if (roll == updateRoll) {
            found = 1;
            char newName[100];
            float newMark;
            printf("New Name (no spaces): ");
            if (scanf("%99s", newName) != 1) { printf("Invalid name.\n"); strcpy(newName, name); }
            printf("New Mark: ");
            if (scanf("%f", &newMark) != 1) { printf("Invalid mark.\n"); newMark = mark; }
            fprintf(temp, "%d %s %.2f\n", roll, newName, newMark);
        } else {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        }
    }
    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student updated!\n");
    else printf("Roll not found!\n");
}

/* ---------- Role menus ---------- */
void adminMenu() {
    int c;
    while (1) {
        printf("\nADMIN MENU\n");
        printf("1.Add Student\n2.Display All Students\n3.Search Student\n4.Update Student\n5.Delete Student\n6.Logout\n");
        printf("Choice: ");
        if (scanf("%d",&c) != 1) { while(getchar()!='\n'); continue; }
        if (c==1) addStudent();
        else if (c==2) displayStudents();
        else if (c==3) searchStudent();
        else if (c==4) updateStudent();
        else if (c==5) deleteStudent();
        else return;
    }
}

void staffMenu() {
    int c;
    while (1) {
        printf("\nSTAFF MENU\n");
        printf("1.Display Students\n2.Search Student\n3.Update Student\n4.Logout\n");
        printf("Choice: ");
        if (scanf("%d",&c) != 1) { while(getchar()!='\n'); continue; }
        if (c==1) displayStudents();
        else if (c==2) searchStudent();
        else if (c==3) updateStudent();
        else return;
    }
}

void userMenu() {
    int c;
    while (1) {
        printf("\nUSER MENU\n");
        printf("1.Display Students\n2.Search Student\n3.Logout\n");
        printf("Choice: ");
        if (scanf("%d",&c) != 1) { while(getchar()!='\n'); continue; }
        if (c==1) displayStudents();
        else if (c==2) searchStudent();
        else return;
    }
}

int main() {
    printf("=== Student Record Management System (SRMS) ===\n");
    if (!login_with_attempts()) {
        return 0;
    }
    printf("Logged in as: %s (role: %s)\n", currentUser, currentRole);

    if (strcmp(currentRole, "admin") == 0) adminMenu();
    else if (strcmp(currentRole, "staff") == 0) staffMenu();
    else userMenu();

    printf("Goodbye!\n");
    return 0;
}
