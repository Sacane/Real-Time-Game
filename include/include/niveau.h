/**
 * \fichier : niveau.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __NIVEAU__H__
#define __NIVEAU__H__


#include <stdbool.h> /* Definis le type `bool` */
#include "objet.h"


typedef struct coordonnees{
  unsigned x;
  unsigned y;
} Coordonnees;


typedef struct {
  Coordonnees taille; /* Taille du niveau */
  Objet** objets; /* Tableau bi-directionnel de largeur taille.x, 
                   * de hauteur taille.y, et dont chaque case 
                   * contient un Objet */
  Coordonnees coo_perso; /* Position actuelle du personnage. */
  unsigned long allure_perso; /* Allure du personnage */
  bool depl_perso_autorise; /* Vaut `true` si  le temps ecoule
                             * depuis le dernier deplacement du
                             * personnage est superieur a son
                             * allure. */
} Niveau, *Plateau;



Plateau malloc_Niveau (Coordonnees taille); /* Effectue les malloc's
                                             * pour obtenir un 
                                             * Niveau* de la taille 
                                             * donnee */
void free_Niveau (Plateau niveau); /* Libere la memoire prise par un
                                    * Niveau */


/**
 * \arg niveau : plateau concernant le déplacement du joueur
 * Deplace le joueur selon une direction renseigné
*/
void deplacer_joueur(Plateau niveau, Direction direction); 


#endif