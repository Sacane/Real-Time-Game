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
    Direction dir_perso; /*Direction actuelle du personnage */
    
} Niveau, *Plateau;



void affiche_coordonnee(Coordonnees coordonnee);

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
void deplacer_joueur(Plateau niveau); 

/**
 * Renvoi true si l'objet est prêt à rentré en contact avec un mur, false sinon.
*/
bool mur_en_contact(Plateau plateau, Objet obj);

/**
 * Renvoi true si l'objet est prêt à rentrer en contact avec le bord du terrain.
*/
bool bordure_en_contact(Plateau plateau, Objet obj);

/*Vérifie et renvoi true si le personnage est s'apprête à rentrer en conflit avec un mur */
bool perso_en_contact(Plateau plateau);

void deplacer_projectile(Plateau plateau);



#endif