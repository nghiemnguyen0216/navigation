//Nghiem Nguyen

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "data_structures.h"

//function: create a new stack
STACK* createStack (int capacity) {
    STACK* stack = (STACK*) malloc (sizeof (STACK));

    //print out error if stack is NULL
    if (stack == NULL) {
        printf ("Error: Out of memory!\n");
        exit (0);
    }

    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (VERTEX*) malloc (stack->capacity * sizeof (VERTEX));
    
return stack;
}

//function: push a vertex into the stack
void pushStack (STACK* stack, VERTEX* pVERTEX) {
    stack->top++;
    if (stack->top == stack->capacity - 1) {
        printf ("Error: Stack is full!\n");
        exit (0);
    }

    stack->array[stack->top] = *pVERTEX;
}

//function: pop a vertex out of the stack
VERTEX popStack (STACK* stack) {
    if (stack == NULL || stack->top == -1) {
        printf ("Error: NULL or empty stack!\n");
        exit (0);
    }

    VERTEX popElement = stack->array[stack->top];
    stack->top--;

return popElement;
}

//function: check if the stack is empty
bool isStackEmpty (STACK* stack) {
    if (stack == NULL || stack->top == -1) {
        return true;
    }
    return false;
}

//function: print out the stack
void printStack (STACK* stack) {
    if (isStackEmpty(stack)) {
        printf ("Error: Stack is empty!\n");
        exit (0);
    }

    for (int ii = 0; ii <= stack->top; ii++) {
        printf ("%d ", stack->array[ii].index);
    }
    printf ("\n");
}