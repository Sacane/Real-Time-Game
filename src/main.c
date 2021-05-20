/**
 * \file main.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the main function of the game
 *
 */

#include <stdio.h>
#include "../include/test.h"
#include "../include/gui.h"
#include "../include/opt.h"
#include "../include/config_stdin.h"

int main(int argc, char* argv[]) {
    
    Board game_board = NULL;
    int mode;

    char* name_file = NULL, *name_folder = NULL;
    mode = COMMAND;
    name_file = (char*)malloc(sizeof(char) * BUFSIZ);
    verif_malloc(name_file);
    bool is_game_board_reached = false;
    name_folder = (char*)malloc(sizeof(char) * BUFSIZ);
    verif_malloc(name_folder);
    opt_management(argc, argv, &mode, name_file, &game_board);
    strcpy(name_folder, "game_boards/");
    if(argc < 2){
        game_board = menu(&mode);
    }
    
    switch(mode){
        case DEBUG:
            main_test();
            break;
        case COMMAND:
            launch_command(game_board, &is_game_board_reached);
            break;
        case GRAPHIC:
            launch(game_board, &is_game_board_reached); 
            break;
        case ERROR:
            printf("An error has occur\n");
            if(NULL != game_board){
                free_board(game_board);    
            }
            free(name_file);
            return EXIT_FAILURE;
        case FOLDER:
            break;
        default:
            break;
    }
    
    if(mode == GRAPHIC || mode == COMMAND){
        (is_game_board_reached) ? printf("Congratuations ! You won !\n") : printf("You lost ! \n");
    }
    if(game_board != NULL)
        free_board(game_board);
    free(name_file);
    free(name_folder);
    return EXIT_SUCCESS;
}

