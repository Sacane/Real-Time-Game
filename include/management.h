/**
 * \fichier : management.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __MANAGEMENT__H__
#define __MANAGEMENT__H__

#include "niveau.h"
#include "tas.h"
#include <string.h>
#include "config_stdin.h"


/**
 * Function to build a heap containing the initial Events of a Level
 * @param coordinates : Coordinates, the coordinates of the player
 * @return Tree, a pointer to a heap
 */
Arbre construit_Tas(Plateau niveau); /* Construit un Tas contenant les
                                     * Evenements initiaux d'un 
                                     * Niveau */


/**
 * Function to activate a player's event
 * @param Board : level, a game board
 * @param heap : Tree, a pointer to a heap
 * @param pos_launcher : Coordinates, coordinates of laucher
 * @param previous_launcher : Event, the player event
 */
void declenche_lanceur(Plateau niveau, Arbre tas, Coordonnees pos_lanceur, Evenement ancien_lanceur);


/**
 * Function to activate the event of a projectile
 * @param heap : Tree, a pointer to a heap
 * @param level : Board, a game board
 * @param pos_projectile : Coordinates, coordinates of a projectile
 * @param projectile : Event, the projectile event
 */
void declenche_projectile(Arbre tas, Plateau niveau, Coordonnees pos_projectile, Evenement projectile); 

/* Execute un Evenement , ce qui peut consister a deplacer un
* objet dans le Niveau , verifier si la partie est terminee,
* ajouter de nouveaux evenements au Tas , etc. */
void execute_evenement ( Evenement e, Arbre tas, Niveau* niveau);

void creer_projectile_selon_direction(Plateau plateau, Direction direction, Coordonnees *pos_projectile, Coordonnees pos_lanceur);

void launch_command(Plateau niveau, bool *is_reached);

#endif