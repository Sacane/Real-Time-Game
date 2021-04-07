#include "../include/tas.h"

int test1 = 0;
int test2 = 0;

static unsigned int verif_pere(int iteration){
	unsigned int tmp;
	tmp = (iteration - 1)/2;

    if(tmp == 0){
        return 0;
    }

	if(iteration%2 == 0){
		tmp = (iteration - 2)/2;
		return tmp;
	}
	if(iteration%2 != 0){
		tmp = (iteration - 1)/2;
		return tmp;
	}
    return tmp;
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

    unsigned int i;
    for(i = 0; i < tas->capacite; i++){
        free(&tas->valeurs[i]);
    }
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


static void defiler(Arbre h, int i)
{
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
	/*change(arbre, arbre->taille-1, valeur);*/
    defiler(arbre, (arbre->taille) -1);
	
}


Evenement ote_minimum(Arbre tas){
	Evenement min;

	min=(tas->valeurs)[0];
	(tas->taille)--;
	/*change(tas, 0, (tas->valeurs)[tas->taille]);*/
    
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