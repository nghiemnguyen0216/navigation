//Nghiem Nguyen
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>

//data structure for vertices in the graph
typedef struct TAG_VERTEX {
    int index;
    int position;       //position of the vertex in the min-heap array
    int predecessor;    //predecessor of the vertex in the shortest path tree
    double key;         //key value of the vertex in the min-heap
    double distance;    //distance from the source vertex
    TAG_VERTEX * next;      //pointer to the next vertex in the adjacency list

}VERTEX;

//data structure for nodes on the adjacency list of the graph
typedef struct TAG_NODE {
    int index;
    int vertex;
    int u;
    int v;
    double weight;
    TAG_NODE *next;
}NODE;

#endif