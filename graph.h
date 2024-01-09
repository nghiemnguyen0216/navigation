//Nghiem Nguyen

#ifndef GRAPH_H
#define GRAPH_H 1
#include "data_structures.h"
#include "heap.h"
#include "stack.h"

typedef struct TAG_GRAPH {
    int numVertices;
    int numEdges;
    int *visited;
    int *predecessor;
    double *distance;
    bool isDirectedGraph;
    VERTEX **V;
    NODE **ADJ;
    
} GRAPH;

GRAPH * readGraph(char * argv[], FILE * inputFile, bool isDirectedGraph, int flagValue);
void stopReading();
void displayInstructions();
void printAdjacencyList(GRAPH * graph, int flagValue);
void singlePair (GRAPH * graph, int initialPosition, int finalPosition);
void printPath(GRAPH * graph, int initialPosition, int finalPosition);
void singleSource(GRAPH * graph, int initialPosition);
void printLength(GRAPH * graph, int initialPosition, int finalPosition);


#endif
