#include "../include/parser.h"


Plateau read_file(char* name_file){

    Plateau res;
    Coordonnees size_level;
    FILE *in;

    in = fopen(name_file, "r");

    fscanf(in, "size = %u x %u", &size_level.x, &size_level.y);
    res = malloc_Niveau(size_level);
    printf("%d x %d\n", res->taille.x, res->taille.y);


    
    fclose(in);
    return res;
}
