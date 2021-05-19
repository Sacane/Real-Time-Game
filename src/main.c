#include <stdio.h>
#include "../include/test.h"
#include "../include/gui.h"
#include "../include/opt.h"
#include "../include/config_stdin.h"

int main(int argc, char* argv[]) {
    
    Board level = NULL;
    int mode;
    char* name_file = NULL, *name_folder = NULL;
    mode = COMMAND;
    name_file = (char*)malloc(sizeof(char) * BUFSIZ);
    verif_malloc(name_file);
    bool is_level_reached = false;
    name_folder = (char*)malloc(sizeof(char) * BUFSIZ);
    verif_malloc(name_folder);
    opt_management(argc, argv, &mode, name_file, &level);
    strcpy(name_folder, "levels/");
    if(level == NULL){
        level = level0();
    }
    
    switch(mode){
        case DEBUG:
            main_test();
            break;
        case COMMAND:
            launch_command(level, &is_level_reached);
            break;
        case GRAPHIC:
            launch(level, &is_level_reached); 
            break;
        case ERROR:
            printf("Une erreur est apparue, sortie du programme\n");
            if(NULL != level){
                free_board(level);    
            }
            free(name_file);
            return EXIT_FAILURE;
        case FOLDER:
            break;
        default:
            break;
    }
    
    if(mode == GRAPHIC || mode == COMMAND){
        (is_level_reached) ? printf("Félicitation vous avez fini le niveau !\n") : printf("Vous avez perdu ! \n");
    }
    if(level != NULL)
        free_board(level);
    free(name_file);
    free(name_folder);
    return EXIT_SUCCESS;
}

