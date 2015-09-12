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

void* thread_acceptance(void* data_array)
  {
    s_client*           client_buff;
    s_acceptance_data*  s_data;
    int                 listener;
    struct sockaddr_in* cli_addr;
    socklen_t           socklen;
    pthread_mutex_t*     mutex;

    s_data = data_array;
    mutex = s_data->mutex;
    listener = s_data->listener;
    cli_addr = s_data->cli_addr;
    socklen = s_data->socklen;
    client_buff = s_data->client;
    client_buff->action_available = 1;
    pthread_mutex_init(&(client_buff->mutex), NULL);
    client_buff->fd = accept(listener, (struct sockaddr *)cli_addr, &socklen);
    my_printf("Host->name : %s\n", s_data->client->name);
    write(client_buff->fd, my_strconcat("Hej!", client_buff->name), my_strlen(my_strconcat("Hej!", client_buff->name)));
    write(client_buff->fd, "\n", my_strlen("\n"));
    pthread_mutex_unlock(mutex);
    pthread_exit(NULL);
  }

void* thread_handle_cycle()
  {
    while(42)
    {
      my_printf("thread_time : OK\n");
      usleep(CYCLE_TIME);
      regen_client_actions();
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
