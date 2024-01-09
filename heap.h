//Nghiem Nguyen

#ifndef HEAP_H
#define HEAP_H
#include "data_structures.h"

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    int key;
    pELEMENT *H;
}MinHeap;

typedef MinHeap *pHEAP;

pHEAP createHeap(int capacity);
void insertHeap(pHEAP heap, pELEMENT element);
pELEMENT extractMin(pHEAP heap);
int decreaseKey(pHEAP heap, int position, double key);
int buildMinHeap(pHEAP heap, int * heapifyCount);
int minHeapify(pHEAP heap, int index, int * heapifyCount);
bool minHeapCheck(MinHeap heap);

#endif
