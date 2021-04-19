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
	if (fils >= (T->taille)-1) 
		return fils;
	if ((T->valeurs)[fils].moment > (T->valeurs)[fils+1].moment) 
		fils++;
	return fils;
}

static void heap_shift_down(Arbre h, unsigned int i)
{
  unsigned int next_i;
  unsigned int max_i = h->taille - 1; /* Indice à ne pas dépasser */
  Evenement tmp;

  assert((h != NULL) && (h->valeurs != NULL) && (i >= 0));
  if (h->taille - 1 == 0)
    return;
  while ((i*2)+1 <= max_i || (i*2)+2 <= max_i) {
    /* S'il y en a, détermine le plus grand des fils */
    next_i = (i*2)+1;
    if (((i*2)+2 <= max_i) &&
        (h->valeurs[next_i].moment > h->valeurs[(i*2)+2].moment))
      next_i = (i*2)+2;
    /* next_i pointe ici sur le plus grand du ou des fils
     * S'il y a lieu, fait l'échange et continue, sinon sort tout de
     * suite.
     */
    if ((h->valeurs[i].moment > h->valeurs[next_i].moment)) {
      tmp = h->valeurs[i];
      h->valeurs[i] = h->valeurs[next_i];
      h->valeurs[next_i] = tmp;
      i = next_i;
    } else
      return;
  }
}



Evenement ote_minimum(Arbre tas){

	assert(tas->valeurs != NULL);
	Evenement min;

    min=(tas->valeurs)[0];

    tas->valeurs[0] = tas->valeurs[tas->taille-1];

    (tas->taille)--;

    heap_shift_down(tas, 0);
    
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
    printf("On affiche le tas :\n");
    unsigned int i;
    printf("[");
    for(i = 0; i < tas->taille; i++){
        affiche_coordonnee(tas->valeurs[i].coo_obj);
        
        if(i != tas->taille-1){
            printf(": %lu, ", tas->valeurs[i].moment);
        }
        else{
            printf(": %lu", tas->valeurs[i].moment);
        }
    }
    printf("]\n");
}

static void creer_projectile_selon_direction(Plateau plateau, Direction direction, Coordonnees *pos_projectile, Coordonnees pos_lanceur){
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    deplacement->allure = 300;
    
    switch(direction){
        case HAUT:
            pos_projectile->x = pos_lanceur.x - 1;
            pos_projectile->y = pos_lanceur.y;
            deplacement->direction = HAUT;
            break;
        case BAS:
            pos_projectile->x = pos_lanceur.x + 1;
            pos_projectile->y = pos_lanceur.y;
            deplacement->direction = BAS;
            break;
        case DROITE:
            pos_projectile->x = pos_lanceur.x;
            pos_projectile->y = pos_lanceur.y + 1;
            deplacement->direction = DROITE;
            break;
        case GAUCHE:
            pos_projectile->x = pos_lanceur.x;
            pos_projectile->y = pos_lanceur.y - 1;
            deplacement->direction = GAUCHE;
            break;
        default:
            printf("Erreur de direction\n");
    }
    plateau->objets[pos_projectile->x][pos_projectile->y].type = PROJECTILE;
    plateau->objets[pos_projectile->x][pos_projectile->y].donnee_suppl = deplacement;
}

void declenche_lanceur(Plateau niveau, Arbre tas, Coordonnees pos_lanceur){
    assert(niveau != NULL);
    assert(tas != NULL);
    assert(niveau->objets[pos_lanceur.x][pos_lanceur.y].type == LANCEUR);
    assert(pos_lanceur.x <= niveau->taille.x);
    assert(pos_lanceur.y <= niveau->taille.y);

    Direction direction;
    Coordonnees pos_projectile;
    Evenement evenement_projectile;
    Evenement evenement_lanceur;
    unsigned long moment_lanceur;
    unsigned long moment = maintenant() + 300;

    for(direction = HAUT; direction <= DROITE; direction++){
        if(!se_dirige_vers_mur(pos_lanceur.x, pos_lanceur.y, direction, niveau)){
            creer_projectile_selon_direction(niveau, direction, &pos_projectile, pos_lanceur);
            evenement_projectile.moment = moment;
            evenement_projectile.coo_obj = pos_projectile;
            ajoute_evenement(tas, evenement_projectile);
        }
    }
    moment_lanceur = maintenant() + 1000;
    evenement_lanceur.moment = moment_lanceur;
    evenement_lanceur.coo_obj = pos_lanceur;
    ajoute_evenement(tas, evenement_lanceur);
}

/*
 (1) - Déplace le projectile : en fonction de la direction
 (2) - si le projectile n'a pas disparu (mur / hors plateau), rajoute dans le tas l'évènement du projectile à la position mis à jour
*/
void declenche_projectile(Arbre tas, Plateau niveau, Coordonnees pos_projectile){

	assert(tas != NULL);
	assert(niveau != NULL);
	assert(pos_projectile.x <= niveau->taille.x);
	assert(pos_projectile.y <= niveau->taille.y);
    assert(niveau->objets[pos_projectile.x][pos_projectile.y].type == PROJECTILE);

    Evenement evenement_projectile;
    
    deplace_projectile(niveau, &pos_projectile);
    unsigned long moment = maintenant() + 300;

	if(pos_projectile.x <= niveau->taille.x && pos_projectile.y <= niveau->taille.y){
		evenement_projectile.moment = moment;
		evenement_projectile.coo_obj = pos_projectile;
		ajoute_evenement(tas, evenement_projectile);
	}
}

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
            declenche_projectile(tas, niveau, coord_evenement);
            break;
        case LANCEUR:
            declenche_lanceur(niveau, tas, coord_evenement);
            break;
        default:
            break;
    }
}