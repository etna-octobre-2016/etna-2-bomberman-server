#include "../lib/my/src/headers/my.h"
#include "./headers/main.h"
#include "./headers/chain_handlers.h"
#include "./headers/init_server.h"
#include "./headers/handler_acceptance_chaining.h"
#include "./headers/threads.h"
#include "./headers/handle_map.h"
#include "./headers/map_player_actions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <math.h>

void* thread_handle_bomb(void* data)
{
  s_client* client;

  client = data;
  my_printf("thread_bomb : OK\n");
  usleep(CYCLE_TIME);
  my_printf("thread_bomb : IGNITIONNNNN\n");
  my_printf("thread_bomb : VOID\n");
  map[client->position_bomb] = SYMBOL_BOMB_IGNITION;
  //TODO function clear all case +1 +1 +1 +1
  usleep(1000000);
  map_bomb_ignition(client);
  client->state_bomb = GET_BOMB;
  //TODO control player presence
  //TODO control modificate SYMBOLE for 1 sec
  //TODO idle all bomb stats
  // action_map_energy_point();
  pthread_exit(NULL);
}
void thread_display_map()
{
  int i;
  int u;
  int row;

  u = sqrt(MAP_SIZE);
  while(42)
  {
    for(i = 0; i < u; i++)
    {
      for(row = i; row < (u * (u)); row += u)
      {
        my_printf(" %d ", map[row]);
      }
      my_printf("\n");
    }
    usleep(CYCLE_TIME);
    }
}
void killThread(pthread_t* threads)
{
  int i;

  for(i = 0; i <= 4; i++)
  {
    pthread_kill(threads[i], 20);
  }
}
