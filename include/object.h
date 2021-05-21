/**
 * \file : object.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions of the file object.c
 *
 */

#ifndef __OBJECT__H__
#define __OBJECT__H__

#include "wrapper.h"

#define INITIAL_SIZE 64

typedef enum {
	EMPTY = 0,          LAUNCHER,           WALL,
	PROJECTILE,   DESTINATION, PLAYER1, PLAYER2,
	SWITCH, DOOR,
} TypeObject;

typedef struct object{
	TypeObject type;     /* Type of the object */
	void* data; /* Data added to the object, Generation  -> Launcher 
											 Deplacement -> Projectile
											 Trigger 	 -> Switch
	 */
	
} Object;

typedef struct {

	Coordinates coo_door; /* Coordinate of the door linked to the switch */

}Trigger;


typedef struct {
	unsigned long intervalle; /*Interval between two projectiles*/
	unsigned long allure_proj; /* Allure of the sent projectiles */
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
 * \param obj : Object*, object to modify
 * \param deplacement : Deplacement*, additional data of the object
 */
void fill_projectile(Object* obj, Deplacement* deplacement);

/**
 * Function to print the type of the object
 * \param object : Object, the type of the object
 * function for @test
 */
void print_kind_object(Object object);


/**
 * Modifies the properties of the launcher object by assigning it the gen generation as a launcher
 * \param launcher : Object*, laucher to fill
 * \param gen : Generation*, a generation 
*/
void fill_launcher(Object* lanceur, Generation* gen);


/**
 * Function to convert a string into an objects (type)
 * \param type : char*, a string of characters 
 * \return TypeObject, the type of the object 
 */
TypeObject str_to_obj(char* type);

/**
 * Function to check if two objects are equal
 * \param obj1 : Object, an object
 * \param obj2 : Object, an object
 * \return bool, true if both objects are equal, false otherwise
 */
bool equals_obj(Object obj1, Object obj2);





#endif