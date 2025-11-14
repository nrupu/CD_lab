#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char transitions[MAX][3][20];  // transitions[i][0]=state1, [1]=input, [2]=state2
int t_count = 0;

char closure[20][20];          // store epsilon closure states
int closure_count = 0;

// Check if state already in closure
int is_in_closure(const char *state) {
    for (int i = 0; i < closure_count; i++) {
        if (strcmp(closure[i], state) == 0)
            return 1;
    }
    return 0;
}

// Add state to closure if not already present
void add_to_closure(const char *state) {
    if (!is_in_closure(state)) {
        strcpy(closure[closure_count++], state);
    }
}

// Recursively find epsilon closure
void find_epsilon_closure(const char *state) {
    add_to_closure(state);
    for (int i = 0; i < t_count; i++) {
        if (strcmp(transitions[i][0], state) == 0 && strcmp(transitions[i][1], "e") == 0) {
            if (!is_in_closure(transitions[i][2])) {
                find_epsilon_closure(transitions[i][2]);
            }
        }
    }
}

int main() {
    FILE *fp = fopen("input.dat", "r");
    if (fp == NULL) {
        printf("Could not open input1.dat\n");
        return 1;
    }

    // Skip header line
    fscanf(fp, "%s %s %s", transitions[t_count][0], transitions[t_count][1], transitions[t_count][2]);

    // Read transitions from file
    while (fscanf(fp, "%s %s %s", transitions[t_count][0], transitions[t_count][1], transitions[t_count][2]) == 3) {
        t_count++;
    }

    fclose(fp);

    char start_state[20];
    printf("Enter the state to compute epsilon closure: ");
    scanf("%s", start_state);

    closure_count = 0;  // reset global closure count
    find_epsilon_closure(start_state);

    printf("\nEpsilon Closure of %s: { ", start_state);
    for (int i = 0; i < closure_count; i++) {
        printf("%s ", closure[i]);
    }
    printf("}\n");

    return 0;
}
