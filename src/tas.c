#include "../include/tas.h"


Arbre malloc_Tas(unsigned capacite_initiale) {
    
	Arbre arbre = (Arbre)malloc(sizeof(Tas));
    verif_malloc(arbre);
	arbre->taille = 0;
	arbre->capacite = capacite_initiale;
	arbre->valeurs = (Evenement*)malloc(capacite_initiale*sizeof(Evenement));
    verif_malloc(arbre->valeurs);

	return arbre; 

}


void free_Tas(Arbre tas){

    unsigned int i;
    for(i = 0; i < tas->capacite; i++){
        free(&tas->valeurs[i]);
    }
    free(tas);
    
}

void realloc_Tas(Arbre tas){
    
    tas->capacite *= 2;
    tas->valeurs = (Evenement*)realloc(tas->valeurs, sizeof(Evenement)*tas->capacite);
    
}

bool un_evenement_est_pret(Arbre tas){
    unsigned i;
    for(i = 0; i < tas->taille; i++){
        if(tas->valeurs[i].moment <= maintenant()){
            return true;
        }
    }
    return false;
}