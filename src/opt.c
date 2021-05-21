/**
 * \file opt.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * Module to manage the different game options 
 *
 */

#include "../include/opt.h"


/**
 * \brief print in the stdout the different usages of the program
*/
void opt_print_usages(){
    printf("===================================================\n");
    printf("Here are the different uses of the proposed program\n");
    printf("===================================================\n\n\n");
    printf("Usage 1 : ./tempsreel test=<int> (from 0 to 3)\nLaunch the program with an exemple level.\n\n");
    printf("Usage 2 : ./tempsreel file=<path_file>\nLaunch the program by reading the level from the given file\n\n");
    printf("Usage 3 : ./tempsreel folder=<int>\n Launch the program by reading all the level in the folder 'levels', you have to specify from which level you want to start\n\n");
    printf("Usage 4 : ./tempsreel mode=<Mode>\nLaunch the program with the following ways : \n\n");
    printf(" -<Mode> = GRAPHIC : Launch the program in graphic mode\n -<Mode> = DEBUG launch the tests used to test the firsts functions to build the project\n\n");
}

/**
 * \fn void opt_management(int argc, char* argv[], int *mode, char *name_file, Board *gameboard)
 * \brief Function to manage the different usage options
 * \param argc : int, the number of arguments
 * \param argv[] : char* [], array of arguments
 * \param mode : int*, a pointer to an int (the chosen mode)
 * \param name_file : char*, string of characters of the name of the given file 
 * \param gameboard : Board *, pointer to a board
 */
void opt_management(int argc, char* argv[], int *mode, char *name_file, Board *gameboard){
    int c, level_number;
    int option_index = 0;
    if(argc < 2){
        *gameboard = level0();
    }
    while(1){

        static struct option long_options[] =
            {
            {"file",     required_argument,       0, 'f'},
            {"test",  required_argument,       0, 't'},
            {"mode",  required_argument, 0, 'm'},
            {"folder", required_argument, 0, 's'},
            {"usage", 0, 0, 'u'},
            {0, 0, 0, 0}
            };
        c = getopt_long (argc, argv, "f:t:m:", long_options, &option_index);
        if(c == -1)
            break;

        switch(c){
            case -1:
                break;
            case 's':
                strcpy(name_file, "levels");
                level_number = strtol(optarg, NULL, 10);
                read_folder(name_file, level_number);
                *mode = FOLDER;
                break;
            case 'f':
                printf("Enter filemode\n");
                strcpy(name_file, optarg);
                printf("program launch with the file : %s %s\n", optarg, name_file);
                *gameboard = read_file(name_file);
                break;
            case 't':
                printf("launch test level %ld\n", strtol(optarg, NULL, 10));
                level_number = strtol(optarg, NULL, 10);
                switch(level_number){
                    case 0:
                        *gameboard = level0();
                        break;
                    case 1:
                        *gameboard = level1();
                        break;
                    case 2: 
                        *gameboard = level2();
                        break;
                    case 3:
                        *gameboard = level3();
                        break;
                    default:
                        printf("Sorry, the level %d can't be launch as Test\n", level_number);
                        *mode = ERROR;
                        break;
                }
                break;
            case 'm':
                if(strcmp(optarg, "DEBUG") == 0){
                    *mode = DEBUG;
                    printf("launch program in debug mode \n");
                }
                else if(strcmp(optarg, "GRAPHIC") == 0){
                    *mode = GRAPHIC;
                    printf("Launch program in graphic mode\n");
                }
                else{
                    printf("unknown mode\n");
                    *mode = ERROR;
                }
                break;
            case 'u':
                opt_print_usages();
                *mode=QUIT;
                break;
            case '?':
                printf("unknown option\n");
                break;
            default:
                abort();
        }
    }
}

/**
 * \brief print the menu and help the player to choose how to build the game_board
 * \param mode : the mode the player has chosen
 * \return the board builded by the player
*/
Board menu(int *mode){

    Board game_board = NULL;
    char c, file_mode;
    int level, dump;
    char *name_file = NULL;

    printf("Welcome to the real-time-game !\n");

    printf("First you have to choose your game mode, select game in command line mode(c) or in graphic mode(g) : ");
    scanf("%c", &c);
    while ((dump = getchar() != '\n') && dump != EOF); /* Dump of the buffer */
    if(c == 'g'){
        printf("Graphic mode chosen\n");
        *mode = GRAPHIC;
    }
    else if(c == 'c'){
        printf("Command line mode chosen\n");
        *mode = COMMAND;
    }
    else{
        *mode = ERROR;
        return NULL;
    }
    
    printf("\nWould you like to type the path to your personnal level's file ? yes(y) or no(n)\n");
    
    scanf("%c", &file_mode);
    while ((dump = getchar() != '\n') && dump != EOF); 
    if(file_mode == 'y'){
        printf("Please type the path to your file : ");
        name_file = (char*)malloc(sizeof(char) * INITIAL_SIZE);
        scanf("%s", name_file);
        if(name_file == NULL){
            printf("NULL\n");
        }
        printf("%s\n", name_file);
        game_board = read_file(name_file);
        printf("\n");
        free(name_file);
    }
    if(file_mode == 'n'){
        printf("Type the level's number you want to play (from 0 to 3):");
        scanf("%d", &level);
        switch(level){
            case 0: 
                game_board = level0();
                break;
            case 1:
                game_board = level1();
                break;
            case 2:
                game_board = level2();
                break;
            case 3:
                game_board = level3();
                break;
            default:
                *mode = ERROR;
                break;
        }
    }

    return game_board;
}