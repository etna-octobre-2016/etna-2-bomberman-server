#include "../lib/my/src/headers/my.h"
#include "./headers/chain_handlers.h"
#include "./headers/main.h"
#include "./headers/handle_map.h"
#include "./headers/map_player_actions.h"
#include "./headers/threads.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <arpa/inet.h>
#include <stdio.h>


int map_player_up(s_client* client)
{
  if (control_wall_presence(client->position - 1) == 0)
  {
    if (client->position == client->position_bomb)
    {
      map[client->position] = SYMBOL_BOMB_IDLE;
    }
    else
    {
      map[client->position] = SYMBOL_VOID;
    }
    map[client->position - 1] = client->map_id;
    client->position -= 1;
    return (1);
  }
  return (0);
}
int map_player_down(s_client* client)
{
  if (control_wall_presence(client->position + 1) == 0)
  {
    if (client->position == client->position_bomb)
    {
      map[client->position] = SYMBOL_BOMB_IDLE;
    }
    else
    {
      map[client->position] = SYMBOL_VOID;
    }
    map[client->position + 1] = client->map_id;
    client->position += 1;
    return (1);
  }
  return (0);
}
int map_player_left(s_client* client)
{
  int ratio_movement;
  int result;

  ratio_movement = sqrt(MAP_SIZE);
  result = 0;
  if (client->position >= ratio_movement)
  {
    if (control_wall_presence(client->position - ratio_movement) == 0)
    {
      if (client->position == client->position_bomb)
      {
        map[client->position] = SYMBOL_BOMB_IDLE;
      }
      else
      {
        map[client->position] = SYMBOL_VOID;
      }
      map[client->position - ratio_movement] = client->map_id;
      client->position -= ratio_movement;
      result = 1;
    }
  }
  return (result);
}
int map_player_right(s_client* client)
{
  int ratio_movement;
  int result;

  ratio_movement = sqrt(MAP_SIZE);
  result = 0;
  if (client->position < (MAP_SIZE - ratio_movement))
  {
    if (control_wall_presence(client->position + ratio_movement) == 0)
    {
      if (client->position == client->position_bomb)
      {
        map[client->position] = SYMBOL_BOMB_IDLE;
      }
      else
      {
        map[client->position] = SYMBOL_VOID;
      }
      map[client->position + ratio_movement] = client->map_id;
      client->position += ratio_movement;
      result = 1;
    }
  }
  return (result);
}
int map_player_bomb(s_client* client)
{
  int return_error;

  if (client->state_bomb == GET_BOMB)
  {
    client->state_bomb = GET_NO_BOMB;
    client->position_bomb = client->position;
    map[client->position] = client->map_id + 1;
    return_error = pthread_create(&(client->thread), NULL, thread_handle_bomb, (void *)client);
      if (return_error != 0)
      {
        perror("pthread_create");
      }
    return (1);
  }
  return (0);
}
void map_bomb_ignition(s_client* client)
{
  int u;

  u = sqrt(MAP_SIZE);
  //control star ignition
  if (client->position_bomb == client->position)
  {
    kill_player(client->map_id);
  }
  map[client->position_bomb] = SYMBOL_VOID;
  if (map[client->position_bomb + u] != SYMBOL_WALL_INDESTRUCTIBLE)
  {
    if (control_player_presence(map[client->position_bomb + u]) == 1)
    {
      kill_player(map[client->position_bomb + u]);
    }
    map[client->position_bomb + u] = SYMBOL_VOID;
  }
  if (map[client->position_bomb - u] != SYMBOL_WALL_INDESTRUCTIBLE)
  {
    if (control_player_presence(map[client->position_bomb - u]) == 1)
    {
      kill_player(map[client->position_bomb - u]);
    }
    map[client->position_bomb - u] = SYMBOL_VOID;
  }
  if (map[client->position_bomb + 1] != SYMBOL_WALL_INDESTRUCTIBLE)
  {
    if (control_player_presence(map[client->position_bomb + 1]) == 1)
    {
      kill_player(map[client->position_bomb + 1]);
    }
    map[client->position_bomb + 1] = SYMBOL_VOID;
  }
  if (map[client->position_bomb - 1] != SYMBOL_WALL_INDESTRUCTIBLE)
  {
    if (control_player_presence(map[client->position_bomb - 1]) == 1)
    {
      kill_player(map[client->position_bomb - 1]);
    }
    map[client->position_bomb - 1] = SYMBOL_VOID;
  }
}
void send_map(s_client* client)
{
  int i;

  for(i = 0; i < MAP_SIZE; i++)
  {
    write(client->fd, &map[i], sizeof(int));
  }
}
