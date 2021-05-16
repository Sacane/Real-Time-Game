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

#include "wrapper.h"

#define INITIAL_SIZE 64

/* ======== Definition du type `Objet` ====================================== */

typedef enum {
	VIDE = 0,          LANCEUR,           MUR,
	PROJECTILE,        PERSONNAGE,        DESTINATION, PIQUES, PLAYER1, PLAYER2,
} TypeObjet;

typedef struct object{
	TypeObjet type;     /* Type de l'objet */
	void* donnee_suppl; /* Donnee supplementaire: son type depend de 
						* `type` ci-dessus :
						* - Deplacement*  si  type == PROJECTILE
						* - Generation* si type == LANCEUR
						* - donnee\_suppl vaut NULL pour les 
						*   autres types. */
	int index;
} Objet, *Obj;





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


/*
 * modifie les propriété de l'objet obj en lui attribuant le déplacement en tant que projectile
*/
void remplis_projectile(Objet* obj, Deplacement* deplacement);

void print_kind_object(Objet object);

/*
 * Modifie les propriétés de l'objet lanceur en lui attribuant la génération gen en tant que lanceur
*/
void remplis_lanceur(Objet* lanceur, Generation* gen);

TypeObjet str_to_obj(char* type);

/* Renvoi true si les deux objet sont égaux, false sinon */
bool equals_obj(Objet obj1, Objet obj2);







#endif