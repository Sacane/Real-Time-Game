#include "../include/opt.h"


void parse_opt(int argc, char* argv[], int *mode, char *name_file){
    int c;
    int option_index = 0;
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
                *mode = TEST_FILE;
                break;
            case 't':
                printf("launch test level %ld\n", strtol(optarg, NULL, 10));
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
                break;
                

            case '?':
                break;
            default:
                abort();
        }
    }
}