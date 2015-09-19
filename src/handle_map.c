#include "../lib/my/src/headers/my.h"
#include "./headers/chain_handlers.h"
#include "./headers/main.h"
#include "./headers/handle_map.h"
#include "./headers/init_server.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

//TODO Function Initialisation pinpoint player + bounderies
//TODO Function handle action players


void init_map()
{
  s_client** clients;
  int i;
  int u;
  int row;

  clients = list_chain->clients_list;
  if ((map = malloc(MAP_SIZE * sizeof(int))) == NULL)
  {
    exit(1);
  }
  u = sqrt(MAP_SIZE);
  //init border
  for(i = 0; i < BACKLOG; i++)
  {
    if (i == 0)
    {
      clients[i]->position = u + 1;
    }
    if (i == 1)
    {
      clients[i]->position = clients[i - 1]->position + ((u - 3) * u);
    }
    if (i == 2)
    {
      clients[i]->position = clients[0]->position + (u - 3);
    }
    if (i == 3)
    {
      clients[i]->position = (MAP_SIZE - 1) - (u + 1);
    }
  }
  //Write Border + Player spawn
  backboning_map();
  //TODO create scenery
  setting_map();
  for(i = 0; i < u; i++)
  {
    for(row = i; row < (u * (u)); row += u)
    {
      my_printf(" %d ", map[row]);
    }
    my_printf("\n");
  }
}

void backboning_map()
{
  s_client** clients;
  int i;
  int u;
  int buffer_u;

  clients = list_chain->clients_list;
  u = sqrt(MAP_SIZE);

  for(i = 0; i <= u; i++)
  {
    map[i] = SYMBOL_WALL_INDESTRUCTIBLE;
  }
  buffer_u = u;
  u += u;
  for(; i < ((MAP_SIZE - 1) - buffer_u); i++)
  {
    if ((i == u) || (i == (u - 1)))
    {
      map[i] = SYMBOL_WALL_INDESTRUCTIBLE;
      if (i == u)
      {
        u += buffer_u;
      }
    }
    else
    {
      map[i] = SYMBOL_VOID;
    }
  }
  for(; i < MAP_SIZE; i++)
  {
    map[i] = SYMBOL_WALL_INDESTRUCTIBLE;
  }
  for(i = 0; i < MAP_SIZE; i++)
  {
    for(u = 0; u < BACKLOG; u++)
    {
      if (clients[u]->position == i)
      {
        map[i] = clients[u]->map_id;
      }
    }
  }
}

void setting_map()
{
  int i;
  int u;

  for(i = 0, u = 0; i < MAP_SIZE; i++)
  {
    if ((map[i] == SYMBOL_VOID) && (control_player_presence(i - 1) == 0))
    {
      if (u == 2)
      {
        map[i] = SYMBOL_WALL_DESTRUCTIBLE;
        u = 0;
      }
      else
      {
        u++;
      }
    }
  }
}

int control_player_presence(int map_id)
{
  s_client* client;

  client = list_chain->first;
  while(client != NULL)
  {
    if (client->map_id == map_id)
    {
      return (1);
    }
    client = client->next;
  }
  return (0);
}

int control_wall_presence(int map_id)
{
  if ((map[map_id] == SYMBOL_WALL_INDESTRUCTIBLE) || (map[map_id] == SYMBOL_WALL_DESTRUCTIBLE) || (map[map_id] == SYMBOL_BOMB_IDLE))
  {
    return (1);
  }
  return (0);
}
