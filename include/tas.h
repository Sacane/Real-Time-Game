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
} Evenement;


typedef struct {
  
	unsigned taille;    /* Nombre d'Evenements contenus dans le tas */
	unsigned capacite;  /* Nombre de cases allouees pour les 
						* `valeurs` (i.e. taille maximale) */
	Evenement* valeurs;/* Tableau d'Evenements de taille `capacite` et
						* dont les `taille` premieres cases sont 
						* utilisees. */
	
} Tas, *Arbre;

bool estTas(Arbre arbre);

Arbre malloc_Tas(unsigned capacite_initiale);


void free_Tas(Arbre tas);
bool est_Tas(Arbre tas);

void realloc_Tas(Arbre tas);

bool un_evenement_est_pret(Arbre tas); 

Evenement ote_minimum(Arbre tas); 
void ajoute_evenement(Arbre tas, Evenement n); 
                                            
									 
void affiche_Tas(Arbre tas);



#endif