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



Arbre construit_Tas(Plateau niveau); /* Construit un Tas contenant les
                                     * Evenements initiaux d'un 
                                     * Niveau */

void declenche_lanceur(Plateau niveau, Arbre tas, Coordonnees pos_lanceur, Evenement ancien_lanceur);

void declenche_projectile(Arbre tas, Plateau niveau, Coordonnees pos_projectile, Evenement projectile); 

/* Execute un Evenement , ce qui peut consister a deplacer un
* objet dans le Niveau , verifier si la partie est terminee,
* ajouter de nouveaux evenements au Tas , etc. */
void execute_evenement ( Evenement e, Arbre tas, Niveau* niveau);

void creer_projectile_selon_direction(Plateau plateau, Direction direction, Coordonnees *pos_projectile, Coordonnees pos_lanceur);

/*int create_projectile_by_direction(Board board, Arbre heap, Direction direction, Coordonnees pos_launcher, unsigned int index, Evenement old_proj, Coordonnees *pos_projectile);

Arbre build_heap_by_board(Board board);

void trigger_launcher(Board board, Arbre heap, Coordonnees coo_launcher, Evenement old_launcher);

void trigger_projectile(Board board, Arbre heap, Evenement ev_proj);
void execute_event(Evenement e, Arbre heap, Board board);*/

#endif