#include <stdio.h>
#include "../include/test.h"
#include "../include/gui.h"
#include "../include/opt.h"
#include "../include/config_stdin.h"

int main(int argc, char* argv[]) {
    
    Plateau niveau = NULL;
    int mode;
    char* name_file = NULL;
    mode = COMMAND;
    name_file = (char*)malloc(sizeof(char) * BUFSIZ);
    bool is_level_reached = false;
    
    opt_management(argc, argv, &mode, name_file, &niveau);
    
    if(niveau == NULL){
        niveau = niveau1test();
    }
    
    switch(mode){
        case DEBUG:
            main_test();
            break;
        case COMMAND:
            launch_command(niveau, &is_level_reached);
            break;
        case GRAPHIC:
            launch(niveau, &is_level_reached); 
            break;
        case ERROR:
            printf("Une erreur est apparue, sortie du programme\n");
            if(NULL != niveau){
                free_Niveau(niveau);    
            }
            free(name_file);
            return EXIT_FAILURE;
        default:
            break;
    }

    if(mode == GRAPHIC || mode == COMMAND){
        (is_level_reached) ? printf("Félicitation vous avez fini le niveau !\n") : printf("Vous avez perdu ! \n");
    }

    free_Niveau(niveau);
    free(name_file);
    return EXIT_SUCCESS;
}

