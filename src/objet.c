#include "../include/objet.h"


void remplis_projectile(Objet* obj, Deplacement* deplacement){

    assert(deplacement != NULL);

    obj->type = PROJECTILE;
    obj->donnee_suppl = deplacement;
}

void remplis_lanceur(Objet* lanceur, Generation* gen){

    assert(gen != NULL);

    lanceur->type = LANCEUR;
    lanceur->donnee_suppl = gen;
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
            memcpy(depl, obj1.donnee_suppl, sizeof(Deplacement));
            memcpy(depl2, obj2.donnee_suppl, sizeof(Deplacement));
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
    if(strcmp(type, "LANCEUR") == 0){
        return LANCEUR;
    }
    if(strcmp(type, "PERSONNAGE") == 0){
        return PERSONNAGE;
    }
    if(strcmp(type, "MUR") == 0){
        return MUR;
    }
    return 0;
}

List_obj malloc_list(Objet obj){
    
    List_obj list = (List_obj) malloc(sizeof(List));
    verif_malloc(list);
    list->obj = obj;
    list->next = NULL; 

    return list;

}


void free_list(List_obj list){
    
    if(list){
        free_list(list->next);
        free(list->obj.donnee_suppl);
        printf("Donnee\n");
        free(list);
        list = NULL;
    }

}

void print_kind_object(Objet object){
    switch(object.type){
        case VIDE:
            printf("EMPTY\n");
            break;
        case MUR:
            printf("WALL\n");
            break;
        case LANCEUR:
            printf("LAUNCHER\n");
            break;
        case PROJECTILE:
            printf("PROJECTILE\n");
            break;
        case PERSONNAGE:
            printf("CHARACTER\n");
            break;
        default:
            printf("Unrecognized kind\n");
            break;
    }
}

void add_obj_in_lst(List_obj *list, Objet obj){
    if(*list != NULL){
        add_obj_in_lst(&((*list)->next), obj);
        return;
    }
    *list = malloc_list(obj);

}

List_obj delete_obj_in_list(List_obj list, Objet obj){
    List_obj tmp, previous;
    if(list == NULL){
        return NULL;
    }
    previous = list;
    if(equals_obj(previous->obj, obj)){
        list = previous->next;
        free(previous);
        return list;
    }
    tmp = previous->next;
    while(tmp != NULL){
        if(equals_obj(tmp->obj, obj)){
            previous->next = tmp->next;
            free(tmp);
            return list;
        }
        previous = tmp;
        tmp = tmp->next;
    }
    return list;
}



