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
    int                 i;
    int                 array_name[4] = {2, 4, 6, 8};


    socklen = sizeof(cli_addr);
    if ((cli_addr = malloc(sizeof(struct sockaddr_in*))) == NULL)
    {
      exit(EXIT_FAILURE);
    }
    if((clients = malloc(4 * sizeof(s_client))) == NULL)
    {
      exit(EXIT_FAILURE);
    }
    for(i = 0; i < BACKLOG; i++)
    {
      if (i != 0)
      {
        clients[i] = add_client();
        clients[i]->map_id = array_name[i];
      }
      else
      {
        client_chain_handler_init();
        clients[i] = list_chain->first;
        clients[i]->map_id = array_name[i];
      }
      pthread_mutex_init(&(clients[i]->mutex), NULL);
      clients[i]->fd = accept(listener, (struct sockaddr *)cli_addr, &socklen);
      my_printf("Host->name : %d\n", clients[i]->map_id);
      // write(clients[i]->fd, clients[i]->map_id, sizeof(int));
      write(clients[i]->fd, "\n", my_strlen("\n"));
    }
    list_chain->clients_list = clients;
  }
