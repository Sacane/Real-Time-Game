#include "../include/parser.h"


Plateau read_file(char* name_file){

    Plateau res;
    unsigned x, y;
    unsigned long allure, intervalle;
    Coordonnees size_level;
    
    FILE *in;
    char *typeObject;
    typeObject = (char*)malloc(sizeof(char) * BUFSIZ);
    
    /*On rentre dans le fichier en vérifiant bien qu'il existe ou non*/
    in = fopen(name_file, "r");
    if(!in){
        fprintf(stderr, "File doesn't exist !\n");
        exit(1);
    }

    /* On récupère la taille du niveau*/
    fscanf(in, "size = %u x %u\n", &size_level.x, &size_level.y);
    res = malloc_Niveau(size_level);
    printf("%d x %d\n", res->taille.x, res->taille.y);
    printf("Filling of the character... ");
    fscanf(in, "PERSONNAGE %u x %u allure : %lu\n", &(res->coo_perso).x, &(res->coo_perso).y, &allure);
    res->allure_perso = une_milliseconde * allure;
    printf("OK || coordinates : (%u, %u) allure : %lu\n", (res->coo_perso).x, (res->coo_perso).y, res->allure_perso);
    printf("Filling of objects...\n");
    while(fscanf(in, "%s", typeObject) != EOF){
        Generation *gen = (Generation*)malloc(sizeof(Generation));
        switch(str_to_obj(typeObject)){
            case LANCEUR:
                printf("Filling of launchers...\n");
                fscanf(in, " %u x %u allure : %lu interval : %lu", &x, &y, &allure, &intervalle);
                res->objets[x][y].type = LANCEUR;
                gen->allure_proj = une_milliseconde * allure;
                gen->intervalle = une_milliseconde * intervalle;
                res->objets[x][y].donnee_suppl = gen;
                printf("... OK : interval %lu, allure : %lu\n", intervalle, allure);
                break;
            case MUR:
                printf("Filling of walls...\n");
                fscanf(in, " %u x %u", &x, &y);
                res->objets[x][y].type = MUR;
                res->objets[x][y].donnee_suppl = NULL;
                break;
                free(gen);
            default:
                break;
        }
    }
    printf("OK\n");
    free(typeObject);
    
    fclose(in);
    return res;
}
