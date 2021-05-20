/**
 * \file heap.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * Module use to manage an heap (data structure), this heap 
 * will store the event used to manage the game, the heap is store by the moment of the event
 *
 */

#include "../include/heap.h"
#include <string.h>


/**
 * \fn static unsigned int father(int i)
 * \brief Check if a value is a father un the heap
 * \param i : int, value to  analyze
 * \return unisigned int
 */ 
static unsigned int father(int i){

    assert(i >= 0);

    if(heap_father_left(i) <= 0){
        return 0;
    }
    return (i % 2 == 0) ? (i - 2) / 2 : (i - 1) / 2;
}


/**
 * \fn bool is_heap(Heap heap)
 * \brief Check if the entire heap is a heap or not.
 * \param heap : Heap, heap to check
 * \return true if the array represent a heap, elsewhere return false
 */ 
bool is_heap(Heap heap){

	assert(heap->values != NULL);
	unsigned int i, pere;

	for(i = (heap->size) - 1; i > 0; i--){

		pere = father(i);
		if((heap->values)[0].moment < pere)
			return false;
		if((heap->values)[pere].moment > (heap->values)[i].moment)
			return false;
	}
	return true;
}


/**
 * \fn Heap malloc_heap(unsigned capacite_initiale)
 * \brief malloc the heap according to the given initial capacity 
 * \param initial_capacity : initial capacity of the heap for the allocation
 * \return : Heap, the allocated heap 
 */ 
Heap malloc_heap(unsigned capacite_initiale) {

    assert(capacite_initiale > 0);
    
	Heap heap = (Heap)malloc(sizeof(Tree));
    verif_malloc(heap);
	heap->size = 0;
	heap->capacite = capacite_initiale;
	heap->values = (Event*)malloc(capacite_initiale*sizeof(Event)); 
    verif_malloc(heap->values);
    
	return heap; 
}


/**
 * \fn void free_heap(Heap heap)
 * \brief Free the memory used by the given heap.
 * \param heap : Heap, heap to free
 */
void free_heap(Heap heap){

    if(heap->values != NULL) free(heap->values);
    free(heap);
}


/**
 * \fn void realloc_heap(Heap heap)
 * \brief realloc the heap if its size is greater than its capacity
 * \param heap : Heap, heap to realloc
*/
void realloc_heap(Heap heap){

    assert(heap->values != NULL);

    heap->capacite *= 2; 
    heap->values = (Event*)realloc(heap->values, sizeof(Event)*heap->capacite);
    
}


/**
 * \fn bool is_event_ready(Heap heap)
 * \param heap : Heap, heap to analyze
 * \return true if there is an event that is ready to be execute, elsewhere return false.
 */
bool is_event_ready(Heap heap){

    assert(heap->values != NULL);

    return (heap->values[0].moment <= maintenant());

}


/**
 * \fn static void shift_up(Heap heap, int i)
 * \brief shift up the element at the index "i" of the heap until heap->values is a heap again
 * \param heap : Heap, heap to analyze
 * \param i : int
 */
static void shift_up(Heap heap, int i) {

    assert(heap->values != NULL);
    assert(i >= 0);
    
    int f = father(i);
    Event tmp;

    if (i == 0) return;
    while (heap->values[f].moment > heap->values[i].moment) { 

        tmp = heap->values[f];
        heap->values[f] = heap->values[i];
        heap->values[i] = tmp;

        i = f;
        if (f == 0)
            return;
        else
            f = father(f);
    }
}


/**
 * \fn void add_event(Heap heap, Event value)
 * \brief Add an event in the heap and update it to make it still be a heap
 * \param heap : Heap, heap where we add the event
 * \param value : Event
*/
void add_event(Heap heap, Event value){
    
	assert(heap->values != NULL);
    assert(heap != NULL);

    heap->values[heap->size] = value;
	(heap->size)++;
    
    if(heap->size >= heap->capacite){
        realloc_heap(heap);
    }

    shift_up(heap, (heap->size) -1);
	
}


/**
 * \fn static void shift_down(Heap h, unsigned int i)
 * \brief shift down the element of the heap at the index "i" until the array is a heap again
 * \param heap : Heap, heap where we add the event
 * \param i : unsigned int
*/
static void shift_down(Heap h, unsigned int i){
    assert(h->values != NULL);
    

    unsigned int next;
    unsigned int max = h->size - 1; 
    Event tmp;

    
    if(h->size == 0){
        return;
    }
    if (h->size - 1 == 0)
        return;
    while ((i * 2) + 1 <= max || (i * 2) + 2 <= max) {
        next = (i * 2) + 1;
        if (((i * 2) + 2 <= max) && (h->values[next].moment > h->values[(i*2)+2].moment))
            next = (i * 2) + 2;
        
        if ((h->values[i].moment > h->values[next].moment)) {
            tmp = h->values[i];
            h->values[i] = h->values[next];
            h->values[next] = tmp;
            i = next;
        } else
            return;
    }
}


/**
 * \fn Event heap_pop(Heap heap)
 * \brief Update the heap by removing the smallest element in the heap, the heap will automatically be update to make it still be a heap
 * \param heap : Heap, heap to update
 * \return Event, the event removed from the heap
*/
Event heap_pop(Heap heap){

	assert(heap->values != NULL);
	Event min;

    min=(heap->values)[0];
    heap->values[0] = heap->values[heap->size-1];
    (heap->size)--;

    shift_down(heap, 0);

    
	return min;
}


/**
 * \fn void print_heap(Heap heap)
 * \brief Print in the stdout the actual heap's state
 * \param heap : Heap, heap to print
 */    
void print_heap(Heap heap){

	assert(heap->values != NULL);
    unsigned int i;
    printf("[");
    for(i = 0; i < heap->size; i++){
        
        if(i != heap->size-1){
            printf("(%u, %u): %lu, ", heap->values[i].coo_obj.x,heap->values[i].coo_obj.y, heap->values[i].moment);
        }
        else{
            printf("(%u, %u): %lu, ", heap->values[i].coo_obj.x,heap->values[i].coo_obj.y, heap->values[i].moment);
        }
    }
    printf("]\n");
}

