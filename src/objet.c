#include "../include/objet.h"


void fill_projectile(Objet* obj, Deplacement* deplacement){

    assert(deplacement != NULL);

    obj->type = PROJECTILE;
    obj->data = deplacement;
}

void fill_launcher(Objet* launcher, Generation* gen){

    assert(gen != NULL);

    launcher->type = LAUNCHER;
    launcher->data = gen;
}

bool equals_obj(Objet obj1, Objet obj2){
    
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

TypeObjet str_to_obj(char* type){
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


