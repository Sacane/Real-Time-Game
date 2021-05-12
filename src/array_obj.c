#include "../include/array_obj.h"



void free_obj(Obj object){
    if(object->donnee_suppl){
        free(object->donnee_suppl);
    }
    free(object);
}

Array malloc_arr_objects(int capacity){
    Array array = NULL;
    array = (Array)malloc(sizeof(Objects));
    verif_malloc(array);
    array->capacity = capacity;
    array->size = 0;
    return array;
}

void free_array_obj(Array array){
    unsigned int i;
    for(i = 0; i < array->size; i++){
        if(array->obj[i].donnee_suppl){
            free_obj(array->obj[i].donnee_suppl);
        }
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
    array->obj[(array->size)++] = obj;


    if(array->size >= array->capacity){
        array->capacity *= 2;
        array = (Array)realloc(array, sizeof(Objet) + array->capacity);
        verif_malloc(array);
    }

    return res;
}

Objet extract_object_in_array(Array array, unsigned int index){
    Objet tmp;
    tmp = array->obj[index];
    if(array->obj[index].donnee_suppl){
        free(array->obj[index].donnee_suppl);
    }

    if(index != array->size){
        array->obj[array->size] = array->obj[index];
    }

    array->size--;
    return tmp;
}

bool is_type_in_lst(Array array, TypeObjet kindObject){
    unsigned int i;
    for(i = 0; i < array->size; i++){
        if(kindObject == array[i].obj->type){
            return true;
        }
    }
    return false;
}