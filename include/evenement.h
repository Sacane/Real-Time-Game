/**
 * \fichier : niveau.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __EVENEMENT__H__
#define __EVENEMENT__H__

#include "niveau.h"


typedef struct {
    unsigned long moment; /* Moment auquel evenement doit avoir lieu en
                        * nombre de "tick" du processeur
                        * Voir Gestion du temps */

    Coordonnees coo_obj; /* Objet affecte */
}Evenement;


typedef struct {
  unsigned taille;    /* Nombre d'Evenements contenus dans le tas */
  unsigned capacite;  /* Nombre de cases allouees pour les 
                       * `valeurs` (i.e. taille maximale) */
  Evenement* valeurs; /* Tableau d'Evenements de taille `capacite` et
                       * dont les `taille` premieres cases sont 
                       * utilisees. */
} Tas;



Tas* malloc_Tas(unsigned capacite_initiale);

void free_Tas(Tas* tas);

/* Renvoie `true` si un 
 * evenement doit etre 
 * effectue. */
bool un_evenement_est_pret(Tas* tas); 

Evenement ote_minimum(Tas* tas); /* Renvoie et retire de `tas` 
                                  * l'Evenement dont le `moment` est 
                                  * le  plus petit. */
void ajoute_evenement(Tas* tas, Evenement n); /* Ajoute un Evenement
                                               * a un Tas */
Tas* construit_Tas(Niveau* niveau); /* Construit un Tas contenant les
                                     * Evenements initiaux d'un 
                                     * Niveau */
void affiche_Tas(Tas* tas); /* Affiche le contenu d'un tas, a des
                             * fins de tests */

/* Traite un Evenement. */
void traite_evenement(Evenement e, Tas* tas, Niveau* niveau); 



#endif