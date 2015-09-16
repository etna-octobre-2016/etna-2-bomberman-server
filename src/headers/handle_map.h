#ifndef SOFTWAR_HANDLEMAP_H
#define SOFTWAR_HANDLEMAP_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#define MAP_SIZE 144
#define SYMBOL_VOID 0
#define SYMBOL_WALL_DESTRUCTIBLE 8
#define SYMBOL_WALL_INDESTRUCTIBLE 7
#define SYMBOL_BOMB 6

int* map;
///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
void init_map();
void backboning_map();
void setting_map();
int control_player_presence(int map_id);


#endif
