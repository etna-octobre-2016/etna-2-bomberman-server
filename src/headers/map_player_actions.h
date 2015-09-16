#ifndef SOFTWAR_HANDLEACTIONS_H
#define SOFTWAR_HANDLEACTIONS_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1


///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
int map_player_up(s_client* client);
int map_player_down(s_client* client);
int map_player_left(s_client* client);
int map_player_right(s_client* client);
int map_player_bomb(s_client* client);



#endif
