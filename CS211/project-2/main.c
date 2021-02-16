#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS211 - Project 02 - 02/14/2021
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
// Note: Portions of code adapted from Nasim Mobasheri
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

// Stack struct
typedef struct StackStruct {
    char*   darr;  /* pointer to dynamic array  */
    int     size;  /* amount of space allocated */
    int     inUse; /* how many values are on the stack */
} Stack;

// Function prototypes
void eval_balance(Stack* s, char input[301], int debugMode);
void init(Stack* s);
int is_empty(Stack* s);
void push(Stack* s, char ch, int debugMode);
void pop(Stack* s, int debugMode);
char top(Stack* s);
void clear(Stack* s);
char get_similar(char ch);

int main (int argc, char** argv) {
    // Setup variables
    char input[301];
    Stack st1;
    init(&st1);
    // Determine if we are in debug mode
    int debugMode = 0;
    if (argc == 2) {
        if (strcmp (argv[1], "-d") == 0) {
            debugMode = 1;
        }
    }
    // Loop until q or Q is inputted
    while (1) {
        // Clear array
        clear(&st1);
        /* get line of input from standard input */
        printf ("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);
        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0') {
            i++;
        }
        input[i] = '\0';
        /* check if user enter q or Q to quit program */
        if ((strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0)) {
            break;
        }
        // Run evaluation algorithm
        eval_balance(&st1, input, debugMode);
    }

    free(st1.darr);
    printf ("\nGoodbye\n");
    return 0;
}

// Evaluates if the input is balanced
void eval_balance(Stack* s, char input[301], int debugMode) {
    int i = 0;
    int throw_err = 0;
    while (input[i] != '\0' && throw_err == 0) {
        // Opening symbol
        if (input[i] == '(' || input[i] == '{' || input[i] == '[' || input[i] == '<') {
            push(s, input[i], debugMode);
        } else if (input[i] == ')' || input[i] == '}' || input[i] == ']' || input[i] == '>') { // Closing symbol
            if (is_empty(s) == 1) { // ERROR 2
                printf("Unbalanced expression. Error 2: missing an opening symbol\n");
                printf("%s\n%*c^ missing %c\n", input, i, ' ', get_similar(input[i]));
                throw_err = 1;
            } else if ((input[i] == ')' && top(s) == '(') || (input[i] == '}' && top(s) == '{')
            || (input[i] == ']' && top(s) == '[') || (input[i] == '>' && top(s) == '<')) { // Ensure match
                pop(s, debugMode);
            } else { // ERROR 1
                printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
                printf("%s\n%*c^ expecting %c\n", input, i, ' ', get_similar(s->darr[s->inUse - 1]));
                throw_err = 1;
            }
        }
        i++;
    }
    // Final error checking
    if (is_empty(s) == 0 && throw_err == 0) { // ERROR 3
        printf("Unbalanced expression. Error 3: missing a closing symbol\n");
        printf("%s\n%*c^ missing %c\n", input, i, ' ', get_similar(s->darr[s->inUse - 1]));
    } else if (throw_err == 0)  { // BALANCED
        printf ("%s\n", input);
        printf("Expression is balanced\n");
    }
}

// Initializes dynamic array
void init(Stack* s) {
    s->size = 4;
    s->darr = (char*) malloc ( sizeof (char) * s->size );
    s->inUse = 0;
}

// Check if stack is empty
int is_empty(Stack* s) {
    if (s->inUse == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Pushes new a new element on the top of the stack
void push(Stack* s, char ch, int debugMode) {
    // Grow array by 4 if full
    if (s->inUse >= s->size) {
        char *temp = s->darr;
        int newSize = s->size + 4;
        s->darr = (char*) malloc(sizeof(char) * newSize);
        for (int i = 0; i < s->size; i++){
            s->darr[i] = temp[i];
        }
        if (debugMode == 1) {
            printf("Stack size increased from %d to %d, a total of %d values were copied \n", s->size, newSize, s->inUse);
        }
        s->size = newSize;
        free(temp);
    }
    // Add value onto the top of the stack
    s->darr[s->inUse] = ch;
    s->inUse = s->inUse + 1;
    if (debugMode == 1) {
        printf ("Character %c was pushed into the stack \n", ch);
    }
}

// Removes the top element off the stack
void pop(Stack* s, int debugMode) {
    if (debugMode == 1) {
        printf("Character %c was popped from the stack \n", (s->darr[s->inUse-1]));
    }
    s->inUse = s->inUse - 1;
}

// Returns the element on the top of the stack
char top(Stack* s) {
    return (s->darr[s->inUse-1]);
}

// Clears the stack
void clear(Stack* s) {
    s->size = 4;
    free(s->darr);
    s->darr = (char*) malloc ( sizeof (char) * s->size );
    s->inUse = 0;
}

// Gets the matching symbol
char get_similar(char ch) {
    if (ch == ')') {
        return '(';
    } else if (ch == '}') {
        return '{';
    } else if (ch == ']') {
        return '[';
    } else if (ch == '>') {
        return '<';
    } else if (ch == '(') {
        return ')';
    } else if (ch == '{') {
        return '}';
    } else if (ch == '[') {
        return ']';
    } else if (ch == '<') {
        return '>';
    }
    return '?';
}
