/**
 * \file object.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * Module use to manipulate the different kind of objects in the game
 *
 */

#include "../include/object.h"


/**
 * \fn void fill_projectile(Object* obj, Deplacement* deplacement)
 * \brief Function that modifies the properties of the object 'obj' by assigning it the displacement as a projectile
 * \param obj : Object*, object to modify
 * \param deplacement : Deplacement*, additional data of the object
 */
void fill_projectile(Object* obj, Deplacement* deplacement){

    assert(deplacement != NULL);

    obj->type = PROJECTILE;
    obj->data = deplacement;
}

/**
 * \fn void fill_launcher(Object* launcher, Generation* gen)
 * \brief  Modifies the properties of the launcher object by assigning it the gen generation as a launcher
 * \param launcher : Object*, laucher to fill
 * \param gen : Generation*, a generation 
*/
void fill_launcher(Object* launcher, Generation* gen){

    assert(gen != NULL);

    launcher->type = LAUNCHER;
    launcher->data = gen;
}


/**
 * \fn bool equals_obj(Object obj1, Object obj2)
 * \brief Function to check if two objects are equal
 * \param obj1 : Object, an object
 * \param obj2 : Object, an object
 * \return bool, true if both objects are equal, false otherwise
 */
bool equals_obj(Object obj1, Object obj2){
    
    Deplacement* depl = malloc(sizeof(Deplacement));
    Deplacement* depl2 = malloc(sizeof(sizeof(Deplacement)));

    if(obj1.type != obj2.type){
        free(depl);
        free(depl2);
        return false;
    }
    switch(obj1.type){
        case PROJECTILE:
            memcpy(depl, obj1.data, sizeof(Deplacement));
            memcpy(depl2, obj2.data, sizeof(Deplacement));
            if(depl->direction != depl2->direction
            || depl->direction != depl2->direction){
                free(depl);
                free(depl2);
                return false;
            }

            break;
        default:    
            break;
    }
    free(depl);
    free(depl2);
    return true;
}


/**
 * \fn TypeObject str_to_obj(char* type)
 * \brief Function to convert a string into an objects (type)
 * \param type : char*, a string of characters 
 * \return TypeObject, the type of the object 
 */
TypeObject str_to_obj(char* type){
    if(strcmp(type, "PROJECTILE") == 0){
        return PROJECTILE;
    }
    if(strcmp(type, "LAUNCHER") == 0){
        return LAUNCHER;
    }
    if(strcmp(type, "WALL") == 0){
        return WALL;
    }
    if(strcmp(type, "SWITCH") == 0){
        return SWITCH;
    }
    if(strcmp(type, "PLAYER1") == 0){
        return PLAYER1;
    }
    if(strcmp(type, "PLAYER2") == 0){
        return PLAYER2;
    }
    if(strcmp(type, "DESTINATION") == 0){
        return DESTINATION;
    }
    return 0;
}


