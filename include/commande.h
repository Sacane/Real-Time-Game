/**
 * \fichier : commande.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __COMMANDE__H__
#define __COMMANDE__H__

#include "niveau.h"


Plateau niveau0();

Plateau niveau1();

Plateau niveau2();
 
Plateau niveau3();

void affiche_Niveau (Plateau niveau); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */



#endif