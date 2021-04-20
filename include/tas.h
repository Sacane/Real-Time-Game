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

#include "niveau.h"
#include "temps.h"

#define heap_father_left(i) ((int) ((i)-1) / 2)
#define heap_father(i) ((int) ((i)+1)/2-1)

typedef struct {
    unsigned long moment; /* Moment auquel evenement doit avoir lieu en
                        * nombre de "tick" du processeur
                        * Voir Gestion du temps */

    Coordonnees coo_obj; /* Objet affecte */
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

/* Renvoie `true` si un 
 * evenement doit etre 
 * effectue. */
bool un_evenement_est_pret(Arbre tas); 

Evenement ote_minimum(Arbre tas); /* Renvoie et retire de `tas` 
                                  * l'Evenement dont le `moment` est 
                                  * le  plus petit. */
void ajoute_evenement(Arbre tas, Evenement n); /* Ajoute un Evenement
                                               * a un Tas */
                                               
Arbre construit_Tas(Plateau niveau); /* Construit un Tas contenant les
                                     * Evenements initiaux d'un 
                                     * Niveau */
									 
void affiche_Tas(Arbre tas); /* Affiche le contenu d'un tas, a des
                             * fins de tests */

/* Traite un Evenement. */
void traite_evenement(Evenement e, Arbre tas, Plateau niveau); 

void declenche_lanceur(Plateau niveau, Arbre tas, Coordonnees pos_lanceur, Evenement ancien_lanceur);

void declenche_projectile(Arbre tas, Plateau niveau, Coordonnees pos_projectile, Evenement projectile); 

/* Execute un Evenement , ce qui peut consister a deplacer un
* objet dans le Niveau , verifier si la partie est terminee ,
* ajouter de nouveaux evenements au Tas , etc. */
void execute_evenement ( Evenement e, Tas* tas , Niveau* niveau);


#endif