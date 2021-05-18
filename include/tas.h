/**
 * \fichier : tas.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __TAS__H__
#define __TAS__H__

#include "wrapper.h"



#define heap_father_left(i) ((int) ((i)-1) / 2)
#define heap_father(i) ((int) ((i)+1)/2-1)

typedef struct {
    unsigned long moment; /* Moment auquel evenement doit avoir lieu en
                        * nombre de "tick" du processeur
                        * Voir Gestion du temps */

    Coordonnees coo_obj; /* coordonnée de Objet affecte */
	unsigned int index; /* index de l'objet affecté */
} Event;


typedef struct {
  
	unsigned taille;    
	unsigned capacite;  
	Event* valeurs;
	
} Tree, *Heap;

bool is_heap(Heap Heap);

Heap malloc_heap(unsigned capacite_initiale);


void free_heap(Heap heap);


void realloc_heap(Heap heap);

bool event_is_ready(Heap heap); 

Event heap_pop(Heap heap); 

void add_event(Heap heap, Event n); 
                                            			 
void print_heap(Heap heap);



#endif