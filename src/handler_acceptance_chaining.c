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
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>


void handler_acceptance_chaining(int listener)
  {
    struct sockaddr_in* cli_addr;
    socklen_t           socklen;
    s_client**          clients;
    pthread_t           threads[4];
    s_acceptance_data*  s_data;
    int                 i;
    char*               array_name[4] = {"1","2","3","4"};
    int                 return_error;
    pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;


    socklen = sizeof(cli_addr);
    cli_addr = malloc(sizeof(struct sockaddr_in*));
    s_data = malloc(sizeof(s_acceptance_data));
    clients = malloc(4 * sizeof(s_client));
    s_data->listener = listener;
    s_data->cli_addr = cli_addr;
    s_data->mutex = &mutex;
    s_data->socklen = socklen;
    for(i = 0; i < BACKLOG; i++)
    {
      pthread_mutex_lock(&mutex);
      if (i != 0)
      {
        clients[i] = add_client(my_strconcat("client_", array_name[i]));
      }
      else
      {
        client_chain_handler_init("client_1");
        clients[i] = list_chain->first;
      }
      //create threads
      s_data->client = clients[i];
      return_error = pthread_create(&(threads[i]), NULL, thread_acceptance, (void *)s_data);
      if (return_error != 0)
      {
        perror("pthread_create");
      }
    }
    if (pthread_mutex_trylock(&mutex) != 0)
      add_clients_list(clients);
  }
