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
	VIDE = 0,          LAUNCHER,           WALL,
	PROJECTILE,   DESTINATION, PIQUES, PLAYER1, PLAYER2,
	SWITCH, DOOR,
} TypeObjet;

typedef struct object{
	TypeObjet type;     /* Type de l'objet */
	void* donnee_suppl; /* Donnee supplementaire: son type depend de 
						* `type` ci-dessus :
						* - Deplacement*  si  type == PROJECTILE
						* - Generation* si type == LANCEUR
						* - donnee\_suppl vaut NULL pour les 
						*   autres types. */
	
} Objet;

typedef struct {

	Coordonnees coo_door;

}Trigger;


typedef struct {
	unsigned long intervalle; /* Intervalle entre deux envois
								* de projectiles */
	unsigned long allure_proj; /* Allure des projectiles envoyes */
} Generation;


typedef enum { 
	NORTH,              
	WEST, 
	SOUTH,               
	EAST,
} Direction;


typedef struct {

	Direction direction; /* Direction du deplacement */
	unsigned long allure; /* Allure du deplacement */

} Deplacement;


/**
 * Function that modifies the properties of the object 'obj' by assigning it the displacement as a projectile
 * @param argc : int, the number of the argument (of the chosen option)
 * @param obj : Object*, object to modify
 * @param deplacement : Deplacement*, additional data of the object
 */
void remplis_projectile(Objet* obj, Deplacement* deplacement);

/**
 * Function to print the type of the object
 * @param object : Object, the type of the object
 * function for @test
 */
void print_kind_object(Objet object);

/*
 * Modifie les propriétés de l'objet lanceur en lui attribuant la génération gen en tant que lanceur
*/
void remplis_lanceur(Objet* lanceur, Generation* gen);


/**
 * Function to convert a string into an objects (type)
 * @param type : char*, a string of characters 
 * @return TypeObjet, the type of the object 
 */
TypeObjet str_to_obj(char* type);

/**
 * Function to check if two objects are equal
 * @param obj1 : Object, an object
 * @param obj2 : Object, an object
 * @return bool, true if both objects are equal, false otherwise
 */
bool equals_obj(Objet obj1, Objet obj2);





#endif