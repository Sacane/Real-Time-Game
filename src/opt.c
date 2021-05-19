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
                

            case '?':
                printf("unknown option\n");
                break;
            default:
                abort();
        }
    }
}