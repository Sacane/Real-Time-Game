/**
 * \fichier : objet.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __OBJET__H__
#define __OBJET__H__

#include <stdio.h>
#include <stdlib.h>

/* ======== Definition du type `Objet` ====================================== */
typedef enum {
  VIDE = 0,          LANCEUR,           MUR,
  PROJECTILE,        PERSONNAGE,        DESTINATION,
} TypeObjet;


typedef struct {
  TypeObjet type;     /* Type de l'objet */
  void* donnee_suppl; /* Donnee supplementaire: son type depend de 
                       * `type` ci-dessus:
                       * - Deplacement*  si  type == PROJECTILE
                       * - Generation* si type == LANCEUR
                       * - donnee\_suppl vaut NULL pour les 
                       *   autres types. */
} Objet;


typedef struct {
  unsigned long intervalle; /* Intervalle entre deux envois
                             * de projectiles */
  unsigned long allure_proj; /* Allure des projectiles envoyes */
} Generation;


typedef enum { 
  HAUT,              
  GAUCHE, 
  BAS,               
  DROITE
} Direction;


typedef struct {
  Direction direction; /* Direction du deplacement */
  unsigned long allure; /* Allure du deplacement */
} Deplacement;



void remplis_projectile(Objet* obj, Deplacement* deplacement);

void remplis_lanceur(Objet* lanceur, Generation* gen);


#endif