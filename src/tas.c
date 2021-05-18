#include "../include/tas.h"
#include <string.h>

static unsigned int verif_pere(int i){

    assert(i >= 0);

    if(heap_father_left(i) <= 0){
        return 0;
    }
    return (i % 2 == 0) ? (i - 2) / 2 : (i - 1) / 2;
}


bool is_heap(Heap heap){

	assert(heap->valeurs != NULL);
	unsigned int i, pere;

	for(i = (heap->taille) - 1; i > 0; i--){

		pere = verif_pere(i);
		if((heap->valeurs)[0].moment < pere)
			return false;
		if((heap->valeurs)[pere].moment > (heap->valeurs)[i].moment)
			return false;
	}
	return true;
}


Heap malloc_heap(unsigned capacite_initiale) {

    assert(capacite_initiale > 0);
    
	Heap heap = (Heap)malloc(sizeof(Tree));
    verif_malloc(heap);
	heap->taille = 0;
	heap->capacite = capacite_initiale;
	heap->valeurs = (Event*)malloc(capacite_initiale*sizeof(Event)); 
    verif_malloc(heap->valeurs);
    
	return heap; 
}

void free_heap(Heap tas){

    if(tas->valeurs != NULL) free(tas->valeurs);
    free(tas);
}

void realloc_heap(Heap tas){

    assert(tas->valeurs != NULL);

    tas->capacite *= 2; 
    tas->valeurs = (Event*)realloc(tas->valeurs, sizeof(Event)*tas->capacite);
    
}


bool is_event_ready(Heap tas){

    assert(tas->valeurs != NULL);

    return (tas->valeurs[0].moment <= maintenant());

}


static void defiler(Heap tas, int i) {

    assert(tas->valeurs != NULL);
    assert(i >= 0);
    
    int f = verif_pere(i);
    Event tmp;

    if (i == 0) return;
    while (tas->valeurs[f].moment > tas->valeurs[i].moment) { 

        tmp = tas->valeurs[f];
        tas->valeurs[f] = tas->valeurs[i];
        tas->valeurs[i] = tmp;

        i = f;
        if (f == 0)
            return;
        else
            f = verif_pere(f);
    }
}


void add_event(Heap heap, Event valeur){
    
	assert(heap->valeurs != NULL);
    assert(heap != NULL);

    heap->valeurs[heap->taille] = valeur;
	(heap->taille)++;
    
    if(heap->taille >= heap->capacite){
        realloc_heap(heap);
    }

    defiler(heap, (heap->taille) -1);
	
}

static void enfiler(Heap h, unsigned int i)
{
    assert(h->valeurs != NULL);
    

    unsigned int next_i;
    unsigned int max_i = h->taille - 1; 
    Event tmp;

    
    if(h->taille == 0){
        return;
    }
    if (h->taille - 1 == 0)
        return;
    while ((i * 2) + 1 <= max_i || (i * 2) + 2 <= max_i) {
        next_i = (i * 2) + 1;
        if (((i * 2) + 2 <= max_i) && (h->valeurs[next_i].moment > h->valeurs[(i*2)+2].moment))
            next_i = (i * 2) + 2;

        if ((h->valeurs[i].moment > h->valeurs[next_i].moment)) {
            tmp = h->valeurs[i];
            h->valeurs[i] = h->valeurs[next_i];
            h->valeurs[next_i] = tmp;
            i = next_i;
        } else
            return;
    }
}



Event heap_pop(Heap tas){

	assert(tas->valeurs != NULL);
	Event min;

    min=(tas->valeurs)[0];
    tas->valeurs[0] = tas->valeurs[tas->taille-1];
    (tas->taille)--;

    enfiler(tas, 0);

    
	return min;
}


void print_heap(Heap tas){

	assert(tas->valeurs != NULL);
    printf("On affiche le tas :\n");
    unsigned int i;
    printf("[");
    for(i = 0; i < tas->taille; i++){
        
        if(i != tas->taille-1){
            printf("(%u, %u): %lu, ", tas->valeurs[i].coo_obj.x,tas->valeurs[i].coo_obj.y, tas->valeurs[i].moment);
        }
        else{
            printf("(%u, %u): %lu, ", tas->valeurs[i].coo_obj.x,tas->valeurs[i].coo_obj.y, tas->valeurs[i].moment);
        }
    }
    printf("]\n");
}

