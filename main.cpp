//Nghiem Nguyen

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<cstring>
#include "main.h"

int main (int argc, char **argv) {
    FILE * inputFile;
    char Action[100];
    int initialPosition;
    int finalPosition;
    bool isDirectedGraph;
    int returnAction = 1;

    if (argc < 4) {
        fprintf(stdout, "Usage: %s <InputFile> <GraphType> <Flag> \n", argv[0]);
        exit(0);
    }

    inputFile = NULL;
    GRAPH * graph = NULL;
    int flagValue = atoi(argv[3]);
    
    //Open file for reading
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        exit(0);
    }

    //Read the graph type for the command line
    if (strcmp(argv[2], "DirectedGraph") == 0) {
        isDirectedGraph = true;
    } else if (strcmp(argv[2], "UndirectedGraph") == 0) {
        isDirectedGraph = false;
    } else {
        printf("Error: Invalid graph type %s\n", argv[2]);
        exit(0);
    }

    //Read the flag value for the command line
    if (flagValue < 1 || flagValue > 3) {
        printf("Error: Cannot open file flag\n");
        exit(0);
    }

    //Create a graph
    graph = readGraph(argv, inputFile, isDirectedGraph, flagValue);

    while(1) {
        returnAction = nextAction(Action, &initialPosition, &finalPosition);

        //Invalid action
        if (returnAction == 0) {
            printf("Error: Invalid action, please try again!\n");
            continue;
        }

        //Stop action
        if (strcmp(Action, "Stop") == 0) {
            stopReading();
            break;
        }

        //Display instructions (1st way)
        if (strcmp(Action, "?") == 0) {
            displayInstructions();
            continue;
        }

        //Display instructions (2nd way)
        if (strcasecmp(Action, "Instruction") == 0) {
            displayInstructions();
            continue;
        }

        //Display instructions (3rd way)
        if (strcasecmp(Action, "Instructions") == 0) {
            displayInstructions();
            continue;
        }
        
        //PrintADJ action
        if (strcmp(Action, "PrintADJ") == 0) {
            printAdjacencyList(graph, flagValue);
            continue;
        }

        if (strcmp(Action, "SinglePair") == 0) {
            singlePair(graph, initialPosition, finalPosition);
            continue;
        }

        if (strcmp(Action, "SingleSource") == 0) {
            singleSource(graph, initialPosition);
            continue;
        }

        if (strcmp(Action, "PrintLength") == 0) {
            printLength(graph, initialPosition, finalPosition);
            continue;
        }

        if (strcmp(Action, "PrintPath") == 0) {
            printPath(graph, initialPosition, finalPosition);
            continue;
        }
    }

    fclose(inputFile);
    return 0;
}