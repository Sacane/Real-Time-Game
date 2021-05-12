#ifndef __ARRAY_OBJ__H__
#define __ARRAY_OBJ__H__


#include "objet.h"


typedef struct objects{
	
	unsigned int size;
	unsigned int capacity;

	Objet *obj;


}Objects, *Array;


Array malloc_arr_objects(int capacity);

void big_free_array(Array array);

int add_object_in_array(Array array, Objet obj);

/* extrait l'objet à l'indice "index" du tableau array */
Objet extract_object_in_array(Array array, unsigned int index);

bool is_type_in_lst(Array lst_obj, TypeObjet kindObject);

#endif