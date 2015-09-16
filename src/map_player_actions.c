#include "../lib/my/src/headers/my.h"
#include "./headers/chain_handlers.h"
#include "./headers/main.h"
#include "./headers/handle_map.h"
#include "./headers/map_player_actions.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

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
  if (client->state_bomb == 0)
  {
    client->state_bomb = 1;
    client->position_bomb = client->position;
    map[client->position] = client->map_id + 1;
    //TODO handle thread bomb
    return (1);
  }
  return (0);
}
