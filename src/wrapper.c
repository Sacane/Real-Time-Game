#include "../include/wrapper.h"



void verif_malloc(void *objet){
    if(NULL == objet){
        fprintf(stderr, "Allocation échoué\n");
        exit(1);
    }
}

char *strcpy_tos(char* text){
    char* res;
    res = (char*)malloc(sizeof(char)* strlen(text));
    res = "";
    int i = 0;
    while(atoi(res) == 0){
        printf("%c\n", text[i]);
        res[i] = text[i];
        i++;
    }
    res[i] = '\0';
    return res;
}

