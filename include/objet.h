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
	PROJECTILE,        PERSONNAGE,        DESTINATION,
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


typedef struct listObj{

    Objet obj;
    struct listObj *next;

}List, *List_obj;


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

/*
 * Modifie les propriétés de l'objet lanceur en lui attribuant la génération gen en tant que lanceur
*/
void remplis_lanceur(Objet* lanceur, Generation* gen);

TypeObjet str_to_obj(char* type);

/* Renvoi true si les deux objet sont égaux, false sinon */
bool equals_obj(Objet obj1, Objet obj2);

/* Alloue l'espace mémoire nécéssaire pour stocker une valeur dans la structure */
List_obj malloc_list(Objet obj);

/* Ajoute une valeur en fin de liste */
void add_obj_in_lst(List_obj *list, Objet obj);

List_obj delete_obj_in_list(List_obj list, Objet obj);

/*Libère l'éspace mémoire de la liste*/
void free_list(List_obj list);





#endif