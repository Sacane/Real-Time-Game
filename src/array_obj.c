#include "../include/array_obj.h"



void free_obj(Objet object){
    if(object.donnee_suppl){
        free(object.donnee_suppl);
    }

}

Array malloc_arr_objects(int capacity){
    Array array = NULL;
    array = (Array)malloc(sizeof(Objects));
    verif_malloc(array);
    array->capacity = capacity;
    array->size = 0;
    array->obj = (Objet*)malloc(sizeof(Objet) * capacity);
    return array;
}

void free_array_obj(Array array){
    unsigned int i;
    for(i = 0; i < array->size; i++){
        free_obj(array->obj[i]);
    }
}

void big_free_array(Array array){

    free_array_obj(array);
    free(array->obj);
    free(array);
}

/* ajoute l'objet dans le tableau, retourne l'indice dans lequel l'objet a été ajouter */
int add_object_in_array(Array array, Objet obj){
    
    int res = array->size;
    array->obj[(array->size)].type = obj.type;
    array->obj[(array->size)].donnee_suppl = NULL;

    if(obj.donnee_suppl){
        switch(obj.type){
            case PROJECTILE:
                array->obj[(array->size)].donnee_suppl = (Deplacement*)malloc(sizeof(Deplacement));
                memcpy(array->obj[(array->size)].donnee_suppl, obj.donnee_suppl, sizeof(Deplacement));
                break;
            case LANCEUR:
                array->obj[(array->size)].donnee_suppl = (Generation*)malloc(sizeof(Generation));
                memcpy(array->obj[(array->size)].donnee_suppl, obj.donnee_suppl, sizeof(Generation));
                break;
            default:
                break;
        }
        
        
        free(obj.donnee_suppl);
    }

    (array->size)++;
    if(array->size >= array->capacity){
        array->capacity *= 2;
        array = (Array)realloc(array, sizeof(Objet) + array->capacity);
        verif_malloc(array);
    }


    return res;
}

Objet extract_object_in_array(Array array, unsigned int index){
    Objet tmp;
    tmp.type = array->obj[index].type;
    tmp.donnee_suppl = NULL;
    if(array->obj[index].donnee_suppl){
        switch(tmp.type){
            case PROJECTILE:
                tmp.donnee_suppl = (Deplacement*)malloc(sizeof(Deplacement));
                memcpy(tmp.donnee_suppl, array->obj[index].donnee_suppl, sizeof(Deplacement));
                break;
            case LANCEUR:
                tmp.donnee_suppl = (Generation*)malloc(sizeof(Generation));
                memcpy(tmp.donnee_suppl, array->obj[index].donnee_suppl, sizeof(Generation));
                break;
            default:
                break;
        }


    }
    else{
        tmp.donnee_suppl = NULL;
    }
    array->obj[index].type = VIDE;
    return tmp;
}

bool is_wall_in_box(Array array){
    if(array->size == 0){
        return false;
    }
    if(array[0].obj->type == MUR){
        return true;
    }
    return false;
}

bool is_type_in_lst(Array array, TypeObjet kindObject){
    unsigned int i;
    if(array->size == 0){
        return false;
    }
    for(i = 0; i < array->size; i++){
        if(kindObject == array[i].obj->type){
            return true;
        }
    }
    return false;
}