#include "../lib/my/src/headers/my.h"
#include "./headers/chain_handlers.h"
#include "./headers/main.h"
#include "./headers/handle_map.h"
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
  int ratio_place_player;
  int buffer_u;

  clients = list_chain->clients_list;
  if ((map = malloc(MAP_SIZE * sizeof(map))) == NULL)
  {
    exit(1);
  }
  u = sqrt(MAP_SIZE);
  ratio_place_player = u / 2;
  //init border
  for(i = 0; i < 4; i++)
  {
    if (i == 0)
    {
      clients[i]->position = u + 1;
    }
    if (i == 1)
    {
      clients[i]->position = clients[i - 1]->position + (ratio_place_player * u);
    }
    if (i == 2)
    {
      clients[i]->position = clients[0]->position + ratio_place_player;
    }
    if (i == 3)
    {
      clients[i]->position = clients[1]->position + ratio_place_player;
    }
  }
  for(i = 0; i <= u; i++)
  {
    map[i] = '\0';
  }
  buffer_u = u;
  u += u;
  for(; i < ((MAP_SIZE - 1) - buffer_u); i++)
  {
    if ((i == u) || (i == (u - 1)))
    {
      map[i] = '\0';
      if (i == u)
      {
        u += buffer_u;
      }
    }
    else
    {
      map[i] = 9;
    }
  }
  for(; i < MAP_SIZE; i++)
  {
    map[i] = '\0';
  }
  for(i = 0; i < MAP_SIZE; i++)
  {
    for(u = 0; u < 4; u++)
    {
      if (clients[u]->position == i)
      {
        map[i] = clients[u]->map_id;
      }
    }
  }

  for(i = 0; i < MAP_SIZE; i++)
  {
    my_printf("map[%d] = %d", i, map[i]);
  }
}
