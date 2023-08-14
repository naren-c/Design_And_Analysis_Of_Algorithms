// Name: Naren Chandrashekhar
// SRN: PES2UG20CS216
#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size) 
{
    heap->size = 0;
    heap->max_size = max_size;
    heap->arr = (int*)malloc(sizeof(int)*max_size);
}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr) 
{
    int child, parent;

    heap->arr[heap->size] = key;
    heap->size += 1;
   
    for(int k = 1; k < heap->size; k++)
    {
        child = k;
        key = heap->arr[child];
        parent = (child-1)/2;

        while ((child > 0) && heap->arr[parent] < key) 
        {
            heap->arr[child] = heap->arr[parent];

            child = parent;
            parent = (child-1)/2;
            (*count_ptr)++;
        }
        heap->arr[child] = key;
    }
}

// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int extract_max(heap_t *heap, int *count_ptr) 
{
    int max = heap->arr[0];

    // Assign last element to first element of heap
    heap->arr[0] = heap->arr[heap->size-1];
    // Reduce number of nodes
    --(heap->size);
    //adjust(heap, *pn);

    int child, parent, key;
    parent = 0;
    key = heap->arr[parent];

    child = 2*parent+1;

    // If left child exists
    while (child < heap->size) 
    { 

        // Right child exists
        if (child+1 < heap->size) 
        {
            // If right node is greater than left
            if (heap->arr[child+1] > heap->arr[child]) 
            {
                ++child;
                (*count_ptr)++;
            }
        }

        // Now child stores index of greater child
        if (key < heap->arr[child]) 
        {
            heap->arr[parent] = heap->arr[child];
            parent = child;
            child = 2*parent+1;
            (*count_ptr)++;
        }
        else {
            break;
        }
    }
    heap->arr[parent] = key;

    return max;
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr) 
{
    for(int i = 0; i < heap->size; i++)
    {
        if(key == heap->arr[i])
        {
            (*count_ptr)++;
            return heap->arr[i];
        }
    }
    return -1;
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr) 
{
    if(heap->size > 0)
    {
        *count_ptr = 0; // No comparisions required as 0th element is the max element
        return heap->arr[0];
    }
    else 
        return -1;
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr) 
{
    int min = heap->arr[0];
    for(int i = 1; i< heap->size; i++)
    {
        if(heap->arr[i]<min)
        {
            min = heap->arr[i];
            (*count_ptr)++;
        }
    }
    return min;
}

// Clears the heap for reuse
void clear_heap(heap_t *heap) 
{
    for(int i =0; i<heap->size; i++)
    {
        heap->arr[i] = 0;
    }
    heap->size = 0;
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap) 
{
    free(heap->arr);
}
