#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 1000
#define NAME_LEN 100
#define ROLLNO_LEN 15
#define GROUPS 4

typedef struct {
    char firstName[NAME_LEN];
    char rollNo[ROLLNO_LEN];
    int age;
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    int count;
} Group;

Group H[GROUPS]; // 4 groups

// Function to calculate hash index
int GroupIndexAndSplit(char *firstName, int age) {
    int sum = 0;
    while (*firstName) {
        sum += *firstName;
        firstName++;
    }
    return (sum + age) % GROUPS;
}

// Function to find and print the group index of a student
void GroupIndexAndSplitOperation(char *firstName, int age) {
    int index = GroupIndexAndSplit(firstName, age);
    printf("%d\n", index);
}

// Function to count and list students in a group
void GroupCountAndList(int k) {
    if (k < 0 || k >= GROUPS) return;

    // Sort students alphabetically
    for (int i = 0; i < H[k].count - 1; i++) {
        for (int j = i + 1; j < H[k].count; j++) {
            if (strcmp(H[k].students[i].firstName, H[k].students[j].firstName) > 0) {
                Student temp = H[k].students[i];
                H[k].students[i] = H[k].students[j];
                H[k].students[j] = temp;
            }
        }
    }

    // Print count and names
    printf("%d", H[k].count);
    for (int i = 0; i < H[k].count; i++) {
        printf(" %s", H[k].students[i].firstName);
    }
    printf("\n");
}

// Function to list students by branch
void GroupListByBranch(int m, char *branch) {
    int found = 0;
    for (int i = 0; i < H[m].count; i++) {
        char *rollBranch = H[m].students[i].rollNo + strlen(H[m].students[i].rollNo) - 2;
        if (strcasecmp(rollBranch, branch) == 0) {
            if (found) printf(" ");
            printf("%s", H[m].students[i].firstName);
            found = 1;
        }
    }
    if (!found) printf("-1");
    printf("\n");
}

// Function to retrieve and display student details by roll number
void StudentDetails(char *rollNumber) {
    for (int i = 0; i < GROUPS; i++) {
        for (int j = 0; j < H[i].count; j++) {
            if (strcmp(H[i].students[j].rollNo, rollNumber) == 0) {
                char *branch = H[i].students[j].rollNo + strlen(H[i].students[j].rollNo) - 2;
                printf("%s %d %s\n", H[i].students[j].firstName, H[i].students[j].age, branch);
                return;
            }
        }
    }
    printf("-1\n");
}

// Function to transfer students by branch from one group to another
void GroupTransferAllByBranch(int sourceM, int targetM, char *branch) {
    int transferCount = 0;
    for (int i = 0; i < H[sourceM].count; i++) {
        char *rollBranch = H[sourceM].students[i].rollNo + strlen(H[sourceM].students[i].rollNo) - 2;
        if (strcasecmp(rollBranch, branch) == 0) {
            H[targetM].students[H[targetM].count++] = H[sourceM].students[i];
            for (int j = i; j < H[sourceM].count - 1; j++) {
                H[sourceM].students[j] = H[sourceM].students[j + 1];
            }
            H[sourceM].count--;
            i--;
            transferCount++;
        }
    }
    printf("%d\n", transferCount);
}

int main() {
    int n;
    scanf("%d", &n);

    // Input student details
    for (int i = 0; i < n; i++) {
        Student s;
        scanf("%s %s %d", s.firstName, s.rollNo, &s.age);
        int index = GroupIndexAndSplit(s.firstName, s.age);
        H[index].students[H[index].count++] = s;
    }

    char op;
    while (scanf(" %c", &op) && op != 'f') {
        if (op == 'a') {
            char firstName[NAME_LEN];
            scanf("%s", firstName);
            int index = GroupIndexAndSplit(firstName, 0);
            GroupIndexAndSplitOperation(firstName, 0); // '0' for demonstration purposes
        } else if (op == 'b') {
            int k;
            scanf("%d", &k);
            GroupCountAndList(k);
        } else if (op == 'c') {
            int m;
            char branch[3];
            scanf("%d %s", &m, branch);
            GroupListByBranch(m, branch);
        } else if (op == 'd') {
            char rollNumber[ROLLNO_LEN];
            scanf("%s", rollNumber);
            StudentDetails(rollNumber);
        } else if (op == 'e') {
            int sourceM, targetM;
            char branch[3];
            scanf("%d %d %s", &sourceM, &targetM, branch);
            GroupTransferAllByBranch(sourceM, targetM, branch);
        }
    }

    return 0;
}
