#include "../lib/my/src/headers/my.h"
#include "./headers/main.h"
#include "./headers/chain_handlers.h"
#include "./headers/init_server.h"
#include "./headers/handler_acceptance_chaining.h"
#include "./headers/threads.h"
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

void* thread_handle_cycle()
  {
    while(42)
    {
      my_printf("thread_time : OK\n");
      usleep(CYCLE_TIME);
      regen_client_actions();
      //TODO control player presence
      //TODO control modificate SYMBOLE for 1 sec
      //TODO idle all bomb stats
      // action_map_energy_point();
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
