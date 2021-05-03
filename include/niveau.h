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

#include "objet.h"



typedef struct Niveau{
    
    Coordonnees taille; 
    Objet** objets; 
    /* Définition du personnage */
    Coordonnees coo_perso; 
    unsigned long allure_perso; 
    bool depl_perso_autorise; 
    Direction dir_perso; 
    unsigned long moment_depl_perso;
    bool est_vivant;
    bool est_niveau_termine;
    Coordonnees coo_destination;
    
} Niveau, *Plateau;



void affiche_coordonnee(Coordonnees coordonnee);

Plateau malloc_Niveau (Coordonnees taille); /* Effectue les malloc's
                                             * pour obtenir un 
                                             * Niveau* de la taille 
                                             * donnee */
void free_Niveau (Plateau niveau); /* Libere la memoire prise par un
                                    * Niveau */


void init_niveaux(Plateau niveau, Coordonnees taille);


/**
 * \arg niveau : plateau concernant le déplacement du joueur
 * Deplace le joueur selon une direction renseigné
*/
void deplace_joueur(Plateau niveau); 


void verifie_mouvement_personnage(Plateau niveau);


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

bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second);

void deplace_projectile(Plateau niveau, Coordonnees *coordonnees);

bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Plateau plateau);

bool est_dans_plateau(Direction direction, Plateau plateau, unsigned int x, unsigned int y);

bool check_level_reached(Plateau niveau);

void affiche_Niveau (Plateau niveau); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */

#endif