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
	arbre->valeurs = (Evenement*)malloc(capacite_initiale*sizeof(Evenement)); 
    verif_malloc(arbre->valeurs);
    
	return arbre; 
}

void free_Tas(Arbre tas){

    if(tas->valeurs != NULL) free(tas->valeurs);
    free(tas);
}

void realloc_Tas(Arbre tas){

    assert(tas->valeurs != NULL);

    tas->capacite *= 2; /*On double la capacité max */
    tas->valeurs = (Evenement*)realloc(tas->valeurs, sizeof(Evenement)*tas->capacite);
    
}


bool un_evenement_est_pret(Arbre tas){

    assert(tas->valeurs != NULL);

    unsigned i;
    for(i = 0; i < tas->taille; i++){
        if(tas->valeurs[i].moment <= maintenant()){
            return true;
        }
    }
    return false;
}


static void defiler(Arbre tas, int i) {

    assert(tas->valeurs != NULL);
    assert(i >= 0);
    
    int f = heap_father(i);
    Evenement tmp;

    if (i == 0) return;
    while (tas->valeurs[f].moment > tas->valeurs[i].moment) { 

        tmp = tas->valeurs[f];
        tas->valeurs[f] = tas->valeurs[i];
        tas->valeurs[i] = tmp;

        i = f;
        if (f == 0)
            return;
        else
            f = heap_father(f);
    }
}


void ajoute_evenement(Arbre arbre, Evenement valeur){
    
	assert(arbre->valeurs != NULL);

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

	assert(T->valeurs != NULL);

	unsigned int fils;
	fils = (indice*2+1);
	if (fils == (T->taille)-1) 
		return fils;
	if ((T->valeurs)[fils].moment > (T->valeurs)[fils+1].moment) 
		fils++;
	return fils;
}


static void change(Arbre T, unsigned int indice, Evenement valeur){

	assert(T->valeurs != NULL);
	assert(valeur.moment > 0);

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

	assert(tas->valeurs != NULL);
    
	Evenement min;

    min=(tas->valeurs)[0];
    (tas->taille)--;
    change(tas, 0, tas->valeurs[tas->taille]);

    
	return min;
}


Arbre construit_Tas(Plateau niveau){
    
	Arbre arbre;
    arbre = malloc_Tas(INITIAL_SIZE); 
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

	assert(tas->valeurs != NULL);

    printf("enter\n");
    unsigned int i;
    for(i = 0; i < tas->taille; i++){
        affiche_coordonnee(tas->valeurs[i].coo_obj);
        printf("\n");
        printf("Moment : %lu\n", tas->valeurs[i].moment);
    }
}



/*void declenche_lanceur(Plateau niveau, Arbre tas, Coordonnees pos_lanceur){
    assert(niveau != NULL);
    assert(tas != NULL);
    assert(niveau->objets[pos_lanceur.x][pos_lanceur.y].type == LANCEUR);
    assert(pos_lanceur.x <= niveau->taille.x);
    assert(pos_lanceur.y <= niveau->taille.y);

    Objet lanceur = niveau->objets[pos_lanceur.x][pos_lanceur.y];
    Generation *gen = lanceur.donnee_suppl;


}*/

void execute_evenement(Evenement e, Arbre tas, Plateau niveau) {

    assert(tas != NULL);
	assert(tas->valeurs != NULL);
    assert(niveau != NULL);
	assert(e.coo_obj.x <= niveau->taille.x);
    assert(e.coo_obj.y <= niveau->taille.y);
    
    Coordonnees coord_evenement;
    coord_evenement.x = e.coo_obj.x;
    coord_evenement.y = e.coo_obj.y;

    /* Lancer l'évènement e */
    switch(niveau->objets[coord_evenement.x][coord_evenement.y].type){
        
        case PROJECTILE:
            
            break;
        case LANCEUR:
            break;
        case PERSONNAGE:
            break;
        default:
            break;
    }

}