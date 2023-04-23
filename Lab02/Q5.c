#include <stdio.h>
#include <stdlib.h>

struct employee {
    int empno; 
    char name[30]; 
    int basic, grade;
};

int main() {
    FILE *fp;
    struct employee emp;
    int prev_empno = 0;

    fp = fopen("EMPLOYEE.TXT", "rb");

    if (fp == NULL) {
        printf("File not found or unable to open the file\n");
        return 0;
    }

    while (fread(&emp, sizeof(struct employee), 1, fp) == 1) {
        if (prev_empno == 0) {
            prev_empno = emp.empno;
        }
        else {
            for (int i = prev_empno + 1; i < emp.empno; i++) {
                printf("Missing Employee Number: %d\n", i);
            }
            prev_empno = emp.empno;
        }
    }

    fclose(fp);
    return 0;
}
