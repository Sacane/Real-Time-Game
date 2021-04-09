#include "../include/tas.h"

static unsigned int verif_pere(int iteration){

    if(iteration == 0){
        return 0;
    }
    return (iteration % 2 == 0) ? (iteration - 2) / 2 : (iteration - 1) / 2;

}

bool est_Tas(Arbre tas){
	
    unsigned int k;

    for(k = tas->taille - 1 ; k > 0; k--){
		
        if((tas->valeurs)[k].moment < (tas->valeurs)[(k-1)/2].moment){
            return false;
        }
    }
    return true;
}

bool estTas(Arbre arbre){
	
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
    
	Arbre arbre = (Arbre)malloc(sizeof(Tas));
    verif_malloc(arbre);
	arbre->taille = 0;
	arbre->capacite = capacite_initiale;
	arbre->valeurs = (Evenement*)malloc(capacite_initiale*sizeof(Evenement)); 
    verif_malloc(arbre->valeurs);
    
	return arbre; 
}

void free_Tas(Arbre tas){

    if(tas->valeurs != NULL) free(tas->valeurs);
    free(tas);
}

void realloc_Tas(Arbre tas){

    tas->capacite *= 2; /*On double la capacité max */
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


static void defiler(Arbre h, int i) {
    int f = heap_father(i);
    Evenement tmp;

    if (i == 0) return;
    while (h->valeurs[f].moment > h->valeurs[i].moment) { 

        tmp = h->valeurs[f];
        h->valeurs[f] = h->valeurs[i];
        h->valeurs[i] = tmp;

        i = f;
        if (f == 0)
            return;
        else
            f = heap_father(f);
    }
}


void ajoute_evenement(Arbre arbre, Evenement valeur){
    
    assert((arbre != NULL) && (arbre->valeurs != NULL));
	if ((NULL == arbre)||(arbre->taille == arbre->capacite)){
        fprintf(stderr, "Erreur de taille, ou arbre inexistant\n");
        printf("Ah\n");
		return;
	}
    

    arbre->valeurs[arbre->taille] = valeur;
	(arbre->taille)++;
    
    if(arbre->taille >= arbre->capacite){
        realloc_Tas(arbre);
    }


    defiler(arbre, (arbre->taille) -1);
	
}

static unsigned int Fils(Arbre T, unsigned int indice){
	unsigned int fils;
	fils = (indice*2+1);
	if (fils == (T->taille)-1) 
		return fils;
	if ((T->valeurs)[fils].moment > (T->valeurs)[fils+1].moment) 
		fils++;
	return fils;
}


static void change(Arbre T, unsigned int indice, Evenement valeur){
	unsigned int f;
    
	if (NULL == T) return;

	if ((indice<=(T)->taille)){
        f = Fils(T, indice);

        if ((T->valeurs)[f].moment < valeur.moment){
        (T->valeurs)[indice]=(T->valeurs)[f];
        change(T, f, valeur);;
        }
        
        if(indice != 0){
            if ((T->valeurs)[(indice-1)/2].moment > valeur.moment){
                (T->valeurs)[indice]=(T->valeurs)[(indice-1)/2];
                change(T,(indice-1)/2,valeur);
            }
        }
	    (T->valeurs)[indice]=valeur;
	}
}


Evenement ote_minimum(Arbre tas){

	Evenement min;

    min=(tas->valeurs)[0];
    (tas->taille)--;
    change(tas, 0, tas->valeurs[tas->taille]);

    
	return min;
}


/*static void triTas(Tas tas, int taille){
	
	int i;
	Tas t;
	t.taille = taille; 
	for (i = 0; i< taille; i++){
		ajoute_evenement(&t, (tas.valeurs)[i]);
	}
	for( i= taille-1 ; i>=0 ; i--){
		(tas.valeurs)[i] = ote_minimum(&t);
	}
}*/


Arbre construit_Tas(Plateau niveau){
    
	Arbre arbre;
    arbre = malloc_Tas(512); 
	Evenement evenement;
	unsigned int i, j;
    
	for(i = 0; i < niveau->taille.x ; i++){
		for(j = 0; j < niveau->taille.y; j++){
			if(niveau->objets[i][j].type == LANCEUR) {
				evenement.coo_obj.x = i;
				evenement.coo_obj.y = j;
				evenement.moment = 1000;
				ajoute_evenement(arbre, evenement);
			}
		}
	}
	
	return arbre;
}


void affiche_Tas(Arbre tas){
    printf("enter\n");
    unsigned int i;
    for(i = 0; i < tas->taille; i++){
        affiche_coordonnee(tas->valeurs[i].coo_obj);
        printf("\n");
        printf("Moment : %lu\n", tas->valeurs[i].moment);
    }
	
}

