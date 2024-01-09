//Nghiem Nguyen

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

typedef struct {
    int top;
    int capacity;
    VERTEX * array;
} STACK;

STACK* createStack (int capacity);
void pushStack (STACK* stack, VERTEX vertex);
VERTEX popStack (STACK* stack);
void printStack (STACK* stack);
bool isStackEmpty (STACK* stack);

#endif