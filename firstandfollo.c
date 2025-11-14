#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n, m = 0;
char a[10][10], f[10];
int flag=0;
void follow(char c);
void first(char c);
void first1(char c);
int main() {
    int i, z;
    char c, ch;

    printf("Enter the number of productions:\n");
    scanf("%d", &n);
    printf("Enter the productions (use $ for epsilon):\n");

    for (i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }

    do {
        m = 0;
        printf("\nEnter element whose FIRST and FOLLOW is to be found: ");
        scanf(" %c", &c);  // space before %c skips newline

        first(c);
        printf("FIRST(%c) = { ", c);
        for (i = 0; i < m; i++)
            printf("%c ", f[i]);
        printf("}\n");

        strcpy(f, "");  // reset buffer
        m = 0;

        follow(c);
        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++)
            printf("%c ", f[i]);
        printf("}\n");

        printf("\nContinue (1 = Yes / 0 = No)? ");
        scanf("%d", &z);
    } while (z == 1);

    return 0;
}

// ---------- FIRST Function ----------
void first(char c) {
    int k;

    // If the symbol is a terminal
    if (!isupper(c)) {
        f[m++] = c;
        return;
    }

    // For each production rule
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {  // production starts with this non-terminal
            if (a[k][3] == 'e') {
                f[m++] = 'e'; // epsilon
            } else if (!isupper(a[k][3])) {
                f[m++] = a[k][3]; // terminal
            } else {
                first(a[k][3]); // non-terminal → recursive
            }
        }
    }
}

// ---------- FOLLOW Function ----------
void follow(char c) {
    int i, j;

    if (a[0][0] == c)
        f[m++] = '$'; // Rule 1: start symbol

    for (i = 0; i < n; i++) {
        for (j = 3; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') {
                    flag = 0;
                    first1(a[i][j + 1]);
                    while (flag == 1) {
    flag = 0;  // reset before checking next
    if (a[i][j + 2] != '\0') {
        first1(a[i][j + 2]);  // next symbol
        j++; // move to next position
    } else if (c != a[i][0]) {
        follow(a[i][0]);  // if nothing left, add FOLLOW of LHS
        break;  // avoid infinite recursion
    } else {
        break;
    }
}

                } else if (a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]);
                }
            }
        }
    }
}

// ---------- FIRST1 Function ----------
void first1(char c) {
    int k;

    if (!isupper(c)) {
        f[m++] = c;
        return;
    }

    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][3] == 'e') {
                flag = 1;
            } else if (!isupper(a[k][3])) {
                f[m++] = a[k][3];
            } else {
                first1(a[k][3]);
            }
        }
    }
}
