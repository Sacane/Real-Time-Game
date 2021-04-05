#include "../include/tas.h"


static unsigned int verif_pere(int iteration){
	unsigned int tmp;
	tmp = (iteration - 1)/2;

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
	
	unsigned int i, pere;

	for(i = 1; i < (arbre->taille); i++){

		pere = verif_pere(i);
		if((arbre->valeurs)[i].moment < (arbre->valeurs)[pere].moment)
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


static int Fils(Arbre T, int indice){

	unsigned int fils;
	fils = (indice*2+1);
	if (fils >= T->taille) 
		return -1;
	if (fils == (T->taille)-1) 
		return fils;
	if ((T->valeurs)[fils].moment > (T->valeurs)[fils+1].moment) 
		fils++;
	return fils;
	
}

static void change(Arbre arbre, unsigned int indice, Evenement valeur){
	
    int f;
    if (NULL == arbre) { return; }
    
    if (indice<=(arbre)->taille){
        f=Fils(arbre, indice);
        if (f!=-1){
            if ((arbre->valeurs)[f].moment < valeur.moment){
                (arbre->valeurs)[indice]=(arbre->valeurs)[f];
                change(arbre, f, valeur);
            }
            
            if (indice !=0){
                if ((arbre->valeurs)[(indice-1)/2].moment > valeur.moment){
                    (arbre->valeurs)[indice]=(arbre->valeurs)[(indice-1)/2];
                    change(arbre,(indice-1)/2,valeur);
                }
            }
            (arbre->valeurs)[indice]=valeur;
        }
    }
}


/*void change(tas *T,int indice, int valeur){
  int f;
  if (NULL == T) {return;}
  if (indice<=(*T)->taille) && (indice>= 0){
    f=fils(*T, indice)
    if f!=-1{
      if (*T->arbre)[f]< valeur{
       (*T->arbre)[indice]=(*T->arbre)[f];
        change(T,f,valeur)
        }
      }
    if indice!=0{
    if (*T->arbre)[(indice-1)/2]>valeur{
        (*T->arbre)[indice]=(*T->arbre)[(indice-1)/2];
        change(T,(indice-1)/2,valeur)
        }
    }
  (*T->arbre)[indice]=valeur
  }
}*/


void ajoute_evenement(Arbre arbre, Evenement valeur){
    
	if ((NULL == arbre)||(arbre->taille == arbre->capacite)){
        fprintf(stderr, "Erreur de taille, ou arbre inexistant\n");
		return;
	}
    
    arbre->valeurs[arbre->taille] = valeur;
	(arbre->taille)++;
	change(arbre, arbre->taille-1, valeur);
	
}


Evenement ote_minimum(Arbre tas){
	Evenement min;

	min=(tas->valeurs)[0];
	(tas->taille)--;
	change(tas, 0, (tas->valeurs)[tas->taille]);
    
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

    unsigned int i;
    for(i = 0; i < tas->taille; i++){
        affiche_coordonnee(tas->valeurs[i].coo_obj);
        printf("Moment : %lu", tas->valeurs[i].moment);
    }
	
}