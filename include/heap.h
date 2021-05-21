/**
 * \file : heap.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions of the file heap.c
 */

#ifndef __HEAP__H__
#define __HEAP__H__

#include "wrapper.h"


#define heap_father_left(i) ((int) ((i)-1) / 2)
#define heap_father(i) ((int) ((i)+1)/2-1)

typedef struct {

    unsigned long moment; 
    Coordinates coo_obj; 
	
} Event;


typedef struct {
  
	unsigned size;    
	unsigned capacite;  
	Event* values;
	
} Tree, *Heap;


/**
 * Check if the entire heap is a heap or not.
 * \param Heap to check
 * \return true if the array represent a heap, elsewhere return false
 */ 
bool is_heap(Heap Heap);


/**
 * malloc the heap according to the given initial capacity 
 * \param initial_capacity : initial capacity of the heap for the allocation
 * \return : the allocated heap 
 */ 
Heap malloc_heap(unsigned initial_capacity);

/**
 * Free the memory used by the given heap.
 * \param heap : heap to free
 */
void free_heap(Heap heap);

/**
 * realloc the heap if its size is greater than its capacity
 * \param heap to realloc
*/
void realloc_heap(Heap heap);

/**
 * \param heap : Heap, heap to analyze
 * \return true if there is an event that is ready to be execute, elsewhere return false.
 */
bool is_event_ready(Heap heap); 

/**
 * update the heap by removing the smallest element in the heap,
 * the heap will automatically be update to make it still be a heap
 * \param heap to update
 * \return the event removed from the heap
*/
Event heap_pop(Heap heap); 


/**
 * add an event in the heap and update it to make it still be a heap
 * \param heap where we add the event
 * \param n event to add in the heap
*/
void add_event(Heap heap, Event n); 
                                           
/**
 * print in the stdout the actual heap's state
 * \param heap to print
 */                                             			 
void print_heap(Heap heap);



#endif