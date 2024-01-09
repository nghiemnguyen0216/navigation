//Nghiem Nguyen

#include<stdio.h>
#include<stdlib.h>
#include "heap.h"
#include "data_structures.h"

//check if the min heap is sorted yet.
bool minHeapCheck(MinHeap heap) {
    double previousKey = 0.0;
    double key = 0.0;
    FILE * file = fopen("inputFile", "r");
    int capacity;
    bool sorted = true;

    for (int ii = 0; ii < capacity; ii++) {
        if (fscanf(file, "%lf", &key) != 1) {
            break;
        }
        if (ii > 0 && key < previousKey) {
            sorted = false;
            break;
        } 
        previousKey = key;
    }

    if (file == NULL) {
        printf("Error: Cannot open the file!\n");
        exit(0);
    }

    fclose(file);
    return sorted;
}

//function: create min heap with capacity
MinHeap * createMinHeap(int capacity) {
    MinHeap * heap = (MinHeap *) malloc(sizeof(MinHeap));
    if (heap == NULL) {
        printf("Error: Cannot allocate memeory for minHeap!\n");
        exit(0);
    
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->H = (pELEMENT *) malloc(sizeof(pELEMENT) * capacity);
    if (heap->H == NULL) {
        printf("Error: Cannot allocate memeory for minHeap array!\n");
        exit(0);
    }

    for (int ii = 0; ii < capacity; ii++) {
        heap->H[ii] = (pELEMENT) malloc(sizeof(ELEMENT));
        if (heap->H[ii] == NULL) {
            printf("Error: memeory is not able to allocate into minHeap array!\n");
            exit(0);
        }
    }

return heap;
}

//function: insert an element into a heap
void insertMinHeap (pHEAP * heap, pELEMENT element) {
    if (heap == NULL) {
        printf("Error: MinHeap is NULL!\n");
        exit(0);
    }

    MinHeap * heapStructure = *heap;

    if (heapStructure->size == heapStructure->capacity) {
        printf("Error: MinHeap is full!\n");
        exit(0);
    }

    int pos = heapStructure->size;                                // Find the insertion position and move the element up the heap
    
    while (pos > 0) {
        int parent = (pos - 1) / 2;                             //create a pointer to the parent of the current element
        if (heapStructure -> H[parent]->key <= element->key) {                     //compare the key of the parent with the key of the current element
            break;
        } else {
            heapStructure -> H[pos] = heapStructure -> H[parent];                 //swap the parent with the current element if the key of the parent is greater
            pos = parent;                                       //update the position of the current element
        }
    }

    heapStructure -> H[pos] = element;                                   //insert the element into the heap
    heapStructure -> size++;                                             //update the size of the heap

}

int decreaseKey(pHEAP heap, int position, double key) {
    //print out error statement if the heap is NULL
    if (heap == NULL) {
        printf("Error: MinHeap is NULL!\n");
        exit(0);
    }

    //print out error statement if the heap is empty
    if (heap->size == 0) {
        printf("Error: MinHeap is empty!\n");
        exit(0);
    }

    double newKey = key;                                             //create a new key to store the new key from user input
    heap->H[position-1]->key = newKey;                               //update the key of the element at position to the new key

     // Perform min-heap operation to maintain the heap property
    while (position > 1 && newKey < heap->H[position/2 - 1]->key) {
        // Swap the element at position with its parent
        ELEMENT *temp = heap->H[position - 1];
        heap->H[position - 1] = heap->H[position/2 - 1];
        heap->H[position/2 - 1] = temp;

        // Update positions for the swapped elements
        heap->H[position - 1]->position = position;
        heap->H[position/2 - 1]->position = position / 2;

        position = position / 2;                                    // Update the current position to the parent
    }       

return 1;
}

int buildMinHeap(pHEAP heap, int * heapifyCount) {
    (*heapifyCount) = 0;

    //sort the heap to satifsy with the property of the min heap
    for (int ii = heap->size/2 - 1; ii >= 0; ii--) {
        minHeapify(heap, ii, heapifyCount);
    }

return (*heapifyCount) - 1;
}

int minHeapify(pHEAP heap, int index, int * heapifyCount) {
    (*heapifyCount)++;

    int smallestValue = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    
    //compare the key of the left child with the key of the current element
    if (leftChild < heap->size && heap->H[leftChild]->key < heap->H[smallestValue]->key) {
        smallestValue = leftChild;

    }

    //compare the key of the right child with the key of the current element
    if (rightChild < heap->size && heap->H[rightChild]->key < heap->H[smallestValue]->key) {
        smallestValue = rightChild;
    }

return 0;
}

//function: extract the minimum element from the heap
pELEMENT extractMin(pHEAP * heapStructure) {

    MinHeap * heap = *heapStructure;
    //print out error statement if the heap is empty
    if (heap == NULL) {
        printf("Error: MinHeap is NULL!\n");
        exit(0);
    }

    //print out error statement if the heap is NULL
    if (heap->size == 0) {
        printf("Error: MinHeap is empty!\n");
        exit(0);
    }

    int count = 0;
    ELEMENT *minElement = heap->H[0];                             //create a pointer to the minimum element in the heap
    double minKey = minElement->key;                              //create a variable to store the key of the minimum element

    ELEMENT *lastElement = heap->H[heap->size - 1];        //create a pointer to the last element in the heap
    heap->H[0] = lastElement;                                     //swap minElement and lastElement
    heap->size--;                                          //decrease the size of the heap by 1
    count += 1;

    int index = 0;
    int leftChild = 2 * index + 1;                                  //create a pointer to the left child of the minElement

    while (leftChild < heap->size) {
        int minChild = leftChild;                                   //a pointer to indicate the minimum child of the left and right child
        int rightChild = 2 * index + 2;                             //create a pointer to the right child of the minElement

    //compare the left and right child to find the minimum child
        if (rightChild < heap->size && heap -> H[rightChild]->key < heap -> H[minChild]->key) {
            minChild = rightChild;
        }

    //compares the current element at index with the minimum child
        if (heap -> H[minChild]->key < heap -> H[index]->key) {
            ELEMENT *temp = heap -> H[index];                       //swap the current element with the minimum child if the key is smaller
            heap -> H[index] = heap -> H[minChild];                 //than the key of the current element
            heap -> H[minChild] = temp;
            count++;
        } else {
            break;
        }

        index = minChild;
        leftChild = 2 * index + 1;  
    }

return minElement;
}
