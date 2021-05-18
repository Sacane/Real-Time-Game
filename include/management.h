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
Arbre construit_Tas(Board niveau); /* Construit un Tas contenant les
                                     * Evenements initiaux d'un 
                                     * Niveau */


/**
 * Function to activate a player's event
 * @param Board : level, a game board
 * @param heap : Tree, a pointer to a heap
 * @param pos_launcher : Coordinates, coordinates of laucher
 * @param previous_launcher : Event, the player event
 */
void declenche_lanceur(Board niveau, Arbre tas, Coordonnees pos_lanceur, Event ancien_lanceur);


/**
 * Function to activate the event of a projectile
 * @param heap : Tree, a pointer to a heap
 * @param level : Board, a game board
 * @param pos_projectile : Coordinates, coordinates of a projectile
 * @param projectile : Event, the projectile event
 */
void declenche_projectile(Arbre tas, Board niveau, Coordonnees pos_projectile, Event projectile); 

/* Execute un Event , ce qui peut consister a deplacer un
* objet dans le Niveau , verifier si la partie est terminee,
* ajouter de nouveaux Events au Tas , etc. */
void execute_event ( Event e, Arbre tas, Board niveau);

void creer_projectile_selon_direction(Board plateau, Direction direction, Coordonnees *pos_projectile, Coordonnees pos_lanceur);

void launch_command(Board niveau, bool *is_reached);

#endif