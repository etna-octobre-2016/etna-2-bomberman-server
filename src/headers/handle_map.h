#ifndef SOFTWAR_HANDLEMAP_H
#define SOFTWAR_HANDLEMAP_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#define MAP_SIZE 144
#define IS_ALIVE 1
#define IS_DEAD 0
#define GET_BOMB 1
#define GET_NO_BOMB 0
#define SYMBOL_VOID 0
#define SYMBOL_WALL_DESTRUCTIBLE 11
#define SYMBOL_WALL_INDESTRUCTIBLE 10
#define SYMBOL_BOMB_IDLE 13
#define SYMBOL_BOMB_IGNITION 13

int* map;
///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
void init_map();
void backboning_map();
void setting_map();
int control_player_presence(int map_id);
int control_wall_presence(int map_id);

#endif
