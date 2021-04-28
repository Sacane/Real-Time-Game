#include "../include/wrapper.h"



void verif_malloc(void *objet){
    if(NULL == objet){
        fprintf(stderr, "Allocation échoué\n");
        exit(1);
    }
}

