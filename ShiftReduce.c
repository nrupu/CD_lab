#include <stdio.h>
#include <string.h>

// Global variables
int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

// Function declarations
void check();
void printResult(int accepted);

int main() {
    // Display grammar
    puts("\nGRAMMAR is:");
    puts("E -> E + E");
    puts("E -> E * E");
    puts("E -> (E)");
    puts("E -> id");

    // Input string
    puts("\nEnter input string: ");
    fgets(a, sizeof(a), stdin);

    // Remove newline character if present
    a[strcspn(a, "\n")] = '\0';

    // Initialize variables
    c = strlen(a);
    strcpy(act, "SHIFT->");

    // Print table header
    puts("\nSTACK\t\tINPUT\t\tACTION");

    // Parsing loop
    for (k = 0, i = 0; j < c; k++, i++, j++) {
        // Case 1: token is 'id'
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t\t%s$\t\t%sid", stk, a, act);
            check();
        }
        // Case 2: token is symbol (+, *, (, ))
        else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t\t%s$\t\t%ssymbol", stk, a, act);
            check();
        }
    }

    // Final acceptance check
    if (stk[0] == 'E' && stk[1] == '\0' && a[0] == ' ') {
        printResult(1); // Accepted
    }  
    else {
        printResult(0); // Rejected
    }

    return 0;
}

// ------------------------------------------------------------
// Function: check()
// Description: Checks for possible reductions on the stack
// ------------------------------------------------------------
void check() {
    strcpy(ac, "REDUCE TO E");

    // Rule 1: E -> id
    for (z = 0; z < c; z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, ac);
            j++;
        }
    }

    // Rule 2: E -> E + E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    // Rule 3: E -> E * E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    // Rule 4: E -> (E)
    for (z = 0; z < c; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t\t%s$\t\t%s", stk, a, ac);
            i = i - 2;
        }
    }
}

// ------------------------------------------------------------
// Function: printResult()
// Description: Prints final ACCEPTED / REJECTED message
// ------------------------------------------------------------
void printResult(int accepted) {
    if (accepted) {
        printf("\n\nInput string is ACCEPTED.\n");
    } else {
        printf("\n\nInput string is REJECTED.\n");
    }
}
