//Nghiem Nguyen
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<cfloat>
#include<stack>
#include<queue>
#include<vector>
#include "graph.h"
using namespace std;

//function: read the graph from the input file
GRAPH * readGraph(char * argv[], FILE * inputFile, bool isDirectedGraph, int flagValue) {
    int edgeIndex;
    int i, u, v, n, m;
    double w;

    //open the input file
    ifstream file(argv[1]);

    //print out error if the input file is NULL
    if (inputFile == NULL) {
    fprintf(stdout, "Error: Cannot open file %s\n", argv[1]);
    exit(0);
    }

    flagValue = atoi(argv[3]);                                      //read the flag value
    file >> n >> m;
    GRAPH * graph = new GRAPH;

    graph->numVertices = n;                                         //read the number of vertices
    graph->numEdges = m;                                            //read the number of edges
    graph->visited = (int *) calloc(n+1, sizeof(int));              //allocate memory for visited array
    graph->predecessor = (int *) calloc(n+1, sizeof(int));          //allocate memory for predecessor array
    graph->distance = (double *) calloc(n+1, sizeof(double));       //allocate memory for distance array
    graph->V = (VERTEX **) malloc((n+1) * sizeof(VERTEX *));        //allocate memory for array of pointers to vertices
    graph->ADJ = (NODE **) malloc((n+1) * sizeof(NODE *));          //allocate memory for array of pointers to nodes

    for (i = 1; i <= n; i++) {
        graph->V[i] = new VERTEX;                                   //allocate memory for a vertex
        graph->ADJ[i] = NULL;                                       //initialize the adjacency list of the vertex
    }

    for (i = 0; i < m; i++) {
        file >> edgeIndex >> u >> v >> w;                           //read the index of the edge, the two vertices, and the weight of the edge
        NODE * node = new NODE;                                     //allocate memory for a node
        node->vertex = v;                                           //read the vertex v
        node->index = edgeIndex;                                    //read the index of the edge
        node->weight = w;                                           //read the weight of the edge

        //build the adjacenlist of the graph using flag = 1
        if (flagValue == 1) {
            node->next = graph->ADJ[u];                                 //add the node to the adjacency list of vertex u
            graph->ADJ[u] = node;                                       //add the node to the adjacency list of vertex u

            if (isDirectedGraph == false) {
                NODE * node1 = new NODE;                                //allocate memory for a node
                node1->vertex = u;                                      //read the vertex u
                node1->index = edgeIndex;                               //read the index of the edge
                node1->weight = w;                                      //read the weight of the edge
                node1->next = graph->ADJ[v];                            //add the node to the adjacency list of vertex v
                graph->ADJ[v] = node1;                                  //add the node to the adjacency list of vertex v
            }
        }
        
        //build the adjacenlist of the graph using flag = 2
        if (flagValue == 2) {
            NODE *current = graph->ADJ[u];
            while (current && current->next) {
                current = current->next;
            }
            if (current) {
                current->next = node;
            } else {
                graph->ADJ[u] = node;
            }

            if (isDirectedGraph == false) {
                NODE * node1 = new NODE;                                //allocate memory for a node
                node1->vertex = u;                                      //read the vertex u
                node1->index = edgeIndex;                               //read the index of the edge
                node1->weight = w;                                      //read the weight of the edge
                NODE *current1 = graph->ADJ[v];
                
                //add the node to the adjacency list of vertex v
                while (current1 && current1->next) {
                    current1 = current1->next;
                }
                
                //if the adjacency list of vertex v is not empty
                if (current1) {
                    current1->next = node1;
                } else {
                    graph->ADJ[v] = node1;
                }
            }
        }
   }

file.close();
return graph;
}

void stopReading() {
    exit(0);
}

void displayInstructions() {
    //Introduction message to users
    printf("  Welcome to the Navigation System Program!\n");
    printf("    This program reads a graph from a specified file and performs various actions based on instructions from stdin.\n");
    printf("    The graph can be either directed or undirected, with n vertices and m edges.\n\n");
    printf("    Valid instructions:\n");
    printf("        Graph printing (PrintADJ): Print the adjacency list of the graph.\n");
    printf("        Path computations (SinglePair and SingleSource): Compute the shortest path from a given source to a given destination (SinglePair) or from a given source to all other vertices (SingleSource).\n");
    printf("        Length/path printing (PrintLength and PrintPath): Print the length of the shortest path from a given source to a given destination (PrintLength) or print the shortest path from a given source to a given destination (PrintPath).\n\n");
    printf("    Please enter one of the following commands:\n");
    printf("        1. Stop\n");
    printf("        2. PrintADJ\n");
    printf("        3. SinglePair <initialPosition> <finalPosition>\n");
    printf("        4. SingleSource <initialPosition>\n");
    printf("        5. PrintLength <initialPosition> <finalPosition>\n");
    printf("        6. PrintPath <initialPosition> <finalPosition>\n\n");
}

void printAdjacencyList (GRAPH * graph, int flagValue) {
    int i;

    //Do not print out the adjacencyList if the flag is less than 1 or greater than 2
    if (flagValue < 1 || flagValue > 2) {
        return;
    }

    for (i = 1; i <= graph->numVertices; i++) {
        NODE * node = graph->ADJ[i];                            //get the adjacency list of the vertex
        fprintf(stdout, "ADJ[%d]:", i);                         //print out the vertex
        while (node != NULL) {
            fprintf(stdout, "-->[%d %d: %.2f]", i, node->vertex, node->weight);    //print out the vertex and the weight of the edge            
            node = node->next;                                                                 //move to the next node
        }
        fprintf(stdout, "\n");
    }

}

//global variables
bool wasSingleSourceCalled = false;
bool wasSinglePairCalled = false;
int calledInitialPosition = -1;
int calledFinalPosition = -1;

//function: find the shortest path from given source and destination values
void singlePair (GRAPH * graph, int initialPosition, int finalPosition) {
    wasSingleSourceCalled = false;
    wasSinglePairCalled = true;

    //print out the instruction line
    if (initialPosition < 1 || initialPosition > graph->numVertices || finalPosition < 1 || finalPosition > graph->numVertices) {
        printf("Error: Invalid vertex index!\n");
        return;
    }

    //print out error if the vertex indexex are the same
    if (initialPosition == finalPosition) {
        printf("Error: Initial position and final position are the same!\n");
        return;
    }

    //print out error if the graph is empty
    if (graph->numVertices == 0) {
        printf("Error: Graph is empty!\n");
        return;
    }

    //Initialize the keys and the predecessor of all vertices
    for (int ii = 1; ii <= graph->numVertices; ii++) {
        graph->V[ii]-> key = DBL_MAX;                               //set the key of the vertex to infinity
        graph->V[ii]-> predecessor = -1;                         //set the predecessor of the vertex to -1
    }

    //Initialize the key of the initial position
    graph->V[initialPosition]-> key = 0;

    //Initialize the priority queue
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > priorityQueue;
    priorityQueue.push(std::make_pair(graph->V[initialPosition]->key, initialPosition));

    //Initialize the distance of all vertices
    for (int ii = 1; ii <= graph->numVertices; ii++) {
        graph->distance[ii] = DBL_MAX;                              //set the distance of the vertex to infinity
    }

    //Initialize the distance of the initial position
    graph->distance[initialPosition] = 0;

    //Initialize the color of all vertices
    for (int ii = 1; ii <= graph->numVertices; ii++) {
        graph->visited[ii] = 0;                                 //set the visited status as 0 (white)
    }

    //while loop to find the shortest path
    while (!priorityQueue.empty()) {
        int u = priorityQueue.top().second;                                    //get the vertex with the smallest key
        priorityQueue.pop();                                                    //remove the vertex from the priority queue

        //if the vertex is not visited
        if (graph->visited[u] == 0) {
            graph->visited[u] = 1;                                           //set the value of the visitied to  1 (grey, visited but not discovered)

            //for loop to find the shortest path
            for (NODE * node = graph -> ADJ[u]; node != NULL; node = node->next) {
                int v = node->vertex;                                           //get the vertex v
                double w = node->weight;                                        //get the weight of the edge

                //if the distance of the vertex v is greater than the distance of the vertex u plus the weight of the edge
                if (graph->distance[v] > graph->distance[u] + w) {
                    graph->distance[v] = graph->distance[u] + w;                //update the distance of the vertex v
                    graph->predecessor[v] = u;                                  //update the predecessor of the vertex v
                    priorityQueue.push(std::make_pair(graph->distance[v], v));  //push the vertex v into the priority queue
                }
            }
        }

        graph->visited[u] = 2;                                              //set the value of visited vertex to 1 (black, visited and discovered)
    }

    //update the value of calledInitialPosition and calledFinalPosition
    calledInitialPosition = initialPosition;
    calledFinalPosition = finalPosition;
}

//function: print out the shortest path from function SinglePair
void printPath (GRAPH * graph, int initialPosition, int finalPosition) {
    //print out error if neither SinglePair nor SingleSource has been called
    if (wasSinglePairCalled == false && wasSingleSourceCalled == false) {
        fprintf(stdout, "Neither SinglePair nor SingleSource were called!\n");
        return;
    }

    //print out error statement if the initial position does not match with the most recent call to SingleSource
    if (wasSingleSourceCalled == true && initialPosition != calledInitialPosition) {
        fprintf(stdout, "Initial position is not matched with SingleSource command!\n");
        return;
    }

    //print out the error statement if the initial/final position matches with the most recent call to SinglePair
    if (wasSinglePairCalled == true && (initialPosition != calledInitialPosition || finalPosition != calledFinalPosition)) {
        fprintf(stdout, "Initial or Final position is not matched with SinglePair command!\n");
        return;
    } 

    //Cretae a stack to store the path for the shortest path
        std::stack<int> path;

    if (wasSingleSourceCalled == false) {
        //Check if the most recent call to SinglePair has been made
        if (graph -> distance[finalPosition] == DBL_MAX) {
            printf("There is no path from %d to %d.\n", initialPosition, finalPosition);
            return;
        }

        //Push all vertices into stack (SinglePair)
        for (int ii = finalPosition; ii != initialPosition; ii = graph->predecessor[ii]) {
            path.push(ii);
        }

        path.push(initialPosition);                 //push the initial position into the stack

        //Print out the path
        fprintf(stdout, "The shortest path from %d to %d is:\n", initialPosition, finalPosition);
        while (!path.empty()) {
            int vertex = path.top();
            path.pop();

            if (!path.empty()) {
                fprintf(stdout, "[%d:    %.2f]-->", vertex, graph->distance[vertex]);
            } else {
                fprintf(stdout, "[%d:    %.2f].", vertex, graph->distance[vertex]);
            }
        }
        fprintf(stdout, "\n");
        
    } else {
        //check if the most recent call to SingleSource has been made
        if (calledInitialPosition != initialPosition) {
            return;
        }

        if (graph -> distance[finalPosition] == DBL_MAX) {
            printf("There is no path from %d to %d.\n", initialPosition, finalPosition);
            return;
        }

        //Push all vertices into stack (SingleSource)
        for (int ii = finalPosition; ii != initialPosition; ii = graph->V[ii]->predecessor) {
            path.push(ii);
        }

        path.push(initialPosition);                 //push the initial position into the stack

        //Print out the path
        fprintf(stdout, "The shortest path from %d to %d is:\n", initialPosition, finalPosition);
        while (!path.empty()) {
            int vertex = path.top();
            path.pop();

            if (!path.empty()) {
                fprintf(stdout, "[%d: %7.2lf]-->", vertex, graph->distance[vertex]);
            } else {
                fprintf(stdout, "[%d: %7.2lf].", vertex, graph->distance[vertex]);
            }
        }
        fprintf(stdout, "\n");
    }
}

//function: compute the shortest path from a given source (initial position) to all other vertices
void singleSource(GRAPH * graph, int initialPosition) {
    wasSingleSourceCalled = true;
    wasSinglePairCalled = false;

    //print out error if the initial position is invalid
    if (initialPosition < 1 || initialPosition > graph->numVertices) {
        printf("Error: Invalid vertex index!\n");
        return;
    }

    //print out error if the graph is empty
    if (graph->numVertices == 0) {
        printf("Error: Graph is empty!\n");
        return;
    }

    //Initialize the calledInitialPosition
    calledInitialPosition = initialPosition;

    //Initialize the keys and the predecessor of all vertices
    for (int ii = 1; ii <= graph->numVertices; ii++) {
        graph->V[ii]-> key = DBL_MAX;                               //set the key of the vertex to infinity
        graph->V[ii]-> predecessor = -1;                          //set the predecessor of the vertex to -1
    } 

    //Initialize the key of the initial position
    graph->V[initialPosition]-> key = 0;

    //Initialize the priority queue
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > priorityQueue;
    priorityQueue.push(std::make_pair(graph->V[initialPosition]->key, initialPosition));

    //Initialize the distance of all vertices
    for (int ii = 1; ii <= graph->numVertices; ii++) {
        graph->distance[ii] = DBL_MAX;                              //set the distance of the vertex to infinity
    }

    //Initialize the distance of the initial position
    graph->distance[initialPosition] = 0;

    //Initialize the color of all vertices using array
    std::vector<int> color(graph->numVertices + 1, 0);          //set the color of the vertex to white as 0, grey as 1, and black as 2

    //while loop to find the shortest path
    while (!priorityQueue.empty()) {
        //get the vertex with the smallest key
        int u = priorityQueue.top().second;
        priorityQueue.pop();                                                    //remove the vertex from the priority queue
        color[u] = 2;                                                           //set the color of the vertex to black (visited and discovered)

        //for loop for each vertex v in the adjacency list of vertex u
            for (NODE * node = graph -> ADJ[u]; node != NULL; node = node->next) {
                int v = node->vertex;                                           //get the vertex v
                double w = node->weight;                                        //get the weight of the edge

                //if the distance of the vertex v is greater than the distance of the vertex u plus the weight of the edge
                if (graph->distance[v] > graph->distance[u] + w) {
                    graph->distance[v] = graph->distance[u] + w;                           //update the distance of the vertex v
                    graph->V[v]->key = graph->distance[v];                                 //update the key of the vertex v
                    graph->V[v]->predecessor = u;                                          //update the predecessor of the vertex v

                // If v is not visited
                if (color[v] == 0) {
                    color[v] = 1;                                                         // Mark v as visited (but not discovered)
                    priorityQueue.push(std::make_pair(graph->V[v]->key, v));              // Add v to the queue
                }
            }
        }
    }   
}

//function: print out the length of the shortest path from function SinglePair
void printLength (GRAPH * graph, int initialPosition, int finalPosition) {
    
    //print out error if the initial position is invalid
    if (initialPosition < 1 || initialPosition > graph->numVertices) {
        printf("Error: Invalid vertex index!\n");
        return;
    }

    //print out error if the graph is empty
    if (graph->numVertices == 0) {
        printf("Error: Graph is empty!\n");
        return;
    }

    //Check if the most recent call to SinglePair has been made
    if (graph -> distance[finalPosition] == DBL_MAX) {
        printf("There is no path from %d to %d.\n", initialPosition, finalPosition);
        return;
    }

    //Print out the length of the shortest path
    fprintf(stdout, "The length of the shortest path from %d to %d is:     %.2f\n", initialPosition, finalPosition, graph->distance[finalPosition]);
}
