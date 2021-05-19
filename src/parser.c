#include "../include/parser.h"


Board read_file(char* name_file){

    Board res;
    unsigned x, y, x2, y2;
    unsigned long allure, intervalle;
    Coordinates size_level, coo_player, coo_switch;
    unsigned long allure_player;
    FILE *in;
    char *typeObject;
    typeObject = (char*)malloc(sizeof(char) * BUFSIZ);
    char multiplayer;

    in = fopen(name_file, "r");
    if(!in){
        fprintf(stderr, "File doesn't exist !\n");
        exit(1);
    }

    fscanf(in, "size = %u x %u\n", &size_level.x, &size_level.y);
    res = malloc_board(size_level);
    printf("%d x %d\n", res->taille.x, res->taille.y);
    printf("check multiplayers\n");
    fscanf(in, "multiplayer : %c\n", &multiplayer);
    if(multiplayer == 'y'){
        printf("Mode multiplayer activated\n");
        res->mulptiplayer_mode = true;
    }
    if(multiplayer == 'n'){
        printf("Mode multiplayer disable\n");
        res->mulptiplayer_mode = false;
    }
    printf("Filling of objects...\n");
    while(fscanf(in, "%s", typeObject) != EOF){
        
        switch(str_to_obj(typeObject)){
            
            Trigger *trigger;
            Generation *gen;
            Coordinates coo_door;
            case LAUNCHER:
                gen = (Generation*)malloc(sizeof(Generation));
                printf("Filling of launchers...\n");
                fscanf(in, " %u x %u allure : %lu interval : %lu", &x, &y, &allure, &intervalle);
                res->objets[x][y].type = LAUNCHER;
                gen->allure_proj = une_milliseconde * allure;
                gen->intervalle = une_milliseconde * intervalle;
                res->objets[x][y].data = gen;
                printf("... OK, datas check : interval %lu, allure : %lu\n", intervalle, allure);
                break;

            case WALL:
                printf("Filling of walls...\n");
                fscanf(in, " %u x %u", &x, &y);
                res->objets[x][y].type = WALL;
                res->objets[x][y].data = NULL;
                printf("OK\n");
                break;

            case DESTINATION:
                printf("Filling destination...");
                fscanf(in, " %u x %u", &x, &y);
                res->objets[x][y].type = DESTINATION;
                coo_switch.x = x;
                coo_switch.y = y;
                res->coo_destination = coo_switch;
                
                printf("OK\n");
               
                break;
            case PLAYER1:
                printf("Filling player1 : ");
                fscanf(in, " %u x %u allure : %lu\n", &x, &y, &allure_player);
                printf("%u, %u\n", x, y);
                coo_player.x = x;
                coo_player.y = y;
                printf(".");
                res->p1 = init_player(coo_player, SOUTH, une_milliseconde * allure_player, PLAYER1);
                printf(".");
                res->objets[coo_player.x][coo_player.y].type = PLAYER1;
                printf("OK\n");
                
                break;
            case PLAYER2:
                printf("Filling player2 : ");
                fscanf(in, " %u x %u allure : %lu", &x, &y, &allure_player);
                printf("%u, %u\n", x, y);
                coo_player.x = x;
                coo_player.y = y;
                printf(".");
                res->p2 = init_player(coo_player, SOUTH, une_milliseconde * allure_player, PLAYER2);
                printf(".");
                res->objets[coo_player.x][coo_player.y].type = PLAYER2;
                printf("OK\n");
                break;
            case SWITCH:
                trigger = (Trigger*)malloc(sizeof(Trigger));
                
                printf("Filling switch : ");
                fscanf(in, " %u x %u DOOR %u x %u", &x, &y, &x2, &y2);
                coo_switch.x = x;
                coo_switch.y = y;
                coo_door.x = x2;
                coo_door.y = y2;
                trigger->coo_door = coo_door;
                res->objets[x][y].type = SWITCH;
                res->objets[x2][y2].type = DOOR;
                res->objets[x][y].data = trigger;
                printf("OK\n");
                break;
            default:
                break;
        }
    }
    printf("Reading file : Success\n");
    free(typeObject);
    fclose(in);
    return res;
}

static char *build_path_level(const char* name_folder, int level_state, char* suffix){

    char *name_folder_cpy, *suffix_cpy, *res;
    char num_char[2];
    size_t sum_len = strlen(suffix) + strlen(name_folder);
    name_folder_cpy = (char*)malloc(sizeof(char)* strlen(name_folder));
    suffix_cpy = (char *)malloc(sizeof(char) * strlen(suffix));

    strcpy(name_folder_cpy, name_folder);   
    strcpy(suffix_cpy, suffix);
    sprintf(num_char, "%d", level_state);

    res = (char*)malloc(sizeof(res) * sum_len + 10);
    strcat( name_folder_cpy, "/level");
    strcat(name_folder_cpy, num_char);
    strcat(name_folder_cpy, suffix);
    strcpy(res, name_folder_cpy);

    free(name_folder_cpy);
    free(suffix_cpy);

    return res;

}

void read_folder(char* name_folder, int level_start, int mode){
    int i;
    char num_char[2];
    char*get;
    
    bool is_reached = false;
    for(i = level_start; i <= MAX_LEVEL; i++){
        sprintf(num_char, "%d", i);
        get = build_path_level(name_folder, i, ".txt");
        printf("%s\n", get);
        Board gameboard = read_file(get);

        launch_command(gameboard, &is_reached);
        
        free(get);
        get = NULL;
        if(is_reached == false){
            break;
        } 
    }
   
}