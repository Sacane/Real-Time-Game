#include "../include/opt.h"


void opt_management(int argc, char* argv[], int *mode, char *name_file, Plateau *niveau){
    int c, level_number;
    int option_index = 0;
    if(argc < 2){
        *niveau = niveau1test();
        printf("Ah\n");
    }
    while(1){

        static struct option long_options[] =
            {
            {"file",     required_argument,       0, 'f'},
            {"test",  required_argument,       0, 't'},
            {"mode",  required_argument, 0, 'm'},
            {0, 0, 0, 0}
            };
        c = getopt_long (argc, argv, "f:t:m:", long_options, &option_index);
        if(c == -1)
            break;

        switch(c){
            case -1:
                break;
            case 'f':
                printf("Enter filemode\n");
                strcpy(name_file, optarg);
                printf("program launch with the file : %s %s\n", optarg, name_file);
                *niveau = read_file(name_file);
                break;
            case 't':
                printf("launch test level %ld\n", strtol(optarg, NULL, 10));
                level_number = strtol(optarg, NULL, 10);
                switch(level_number){
                    case 0:
                        *niveau = niveau0();
                        break;
                    case 1:
                        *niveau = niveau1();
                        break;
                    case 2: 
                        *niveau = niveau2();
                        break;
                    case 3:
                        *niveau = niveau3();
                        break;
                    default:
                        printf("Le niveau selectionner n'existe pas\n");
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
                    printf("Mode inconnue\n");
                    *mode = ERROR;
                }
                break;
                

            case '?':
                printf("On sort\n");
                break;
            default:
                abort();
        }
    }
}