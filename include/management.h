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

#endif