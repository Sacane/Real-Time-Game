#include "../include/tas.h"
#include <string.h>

static unsigned int verif_pere(int i){

    assert(i >= 0);

    if(heap_father_left(i) <= 0){
        return 0;
    }
    return (i % 2 == 0) ? (i - 2) / 2 : (i - 1) / 2;
}


bool estTas(Arbre arbre){

	assert(arbre->valeurs != NULL);
	unsigned int i, pere;

	for(i = (arbre->taille) - 1; i > 0; i--){

		pere = verif_pere(i);
		if((arbre->valeurs)[0].moment < pere)
			return false;
		if((arbre->valeurs)[pere].moment > (arbre->valeurs)[i].moment)
			return false;
	}
	return true;
}


Arbre malloc_Tas(unsigned capacite_initiale) {

    assert(capacite_initiale > 0);
    
	Arbre arbre = (Arbre)malloc(sizeof(Tas));
    verif_malloc(arbre);
	arbre->taille = 0;
	arbre->capacite = capacite_initiale;
	arbre->valeurs = (Event*)malloc(capacite_initiale*sizeof(Event)); 
    verif_malloc(arbre->valeurs);
    
	return arbre; 
}

void free_Tas(Arbre tas){

    if(tas->valeurs != NULL) free(tas->valeurs);
    free(tas);
}

void realloc_Tas(Arbre tas){

    assert(tas->valeurs != NULL);

    tas->capacite *= 2; 
    tas->valeurs = (Event*)realloc(tas->valeurs, sizeof(Event)*tas->capacite);
    
}


bool un_evenement_est_pret(Arbre tas){

    assert(tas->valeurs != NULL);

    return (tas->valeurs[0].moment <= maintenant());

}


static void defiler(Arbre tas, int i) {

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


void ajoute_evenement(Arbre arbre, Event valeur){
    
	assert(arbre->valeurs != NULL);
    assert(arbre != NULL);

    arbre->valeurs[arbre->taille] = valeur;
	(arbre->taille)++;
    
    if(arbre->taille >= arbre->capacite){
        realloc_Tas(arbre);
    }

    defiler(arbre, (arbre->taille) -1);
	
}

static void enfiler(Arbre h, unsigned int i)
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



Event ote_minimum(Arbre tas){

	assert(tas->valeurs != NULL);
	Event min;

    min=(tas->valeurs)[0];
    tas->valeurs[0] = tas->valeurs[tas->taille-1];
    (tas->taille)--;

    enfiler(tas, 0);

    
	return min;
}


void affiche_Tas(Arbre tas){

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

