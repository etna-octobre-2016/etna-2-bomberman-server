#ifndef SOFTWAR_HANDLEMAP_H
#define SOFTWAR_HANDLEMAP_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#define MAP_SIZE 144
#define SYMBOL_VOID 0
#define SYMBOL_WALL_DESTRUCTIBLE 9
#define SYMBOL_WALL_INDESTRUCTIBLE 10
#define SYMBOL_BOMB_IDLE 11
#define SYMBOL_BOMB_IGNITION 12

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
