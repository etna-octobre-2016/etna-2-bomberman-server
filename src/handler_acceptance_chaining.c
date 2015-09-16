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
    char*               array_name[5] = {"1","2","3","4","5"};


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
        clients[i] = add_client(my_strconcat("client_", array_name[i]));
      }
      else
      {
        client_chain_handler_init("client_1");
        clients[i] = list_chain->first;
      }
      pthread_mutex_init(&(clients[i]->mutex), NULL);
      clients[i]->fd = accept(listener, (struct sockaddr *)cli_addr, &socklen);
      my_printf("Host->name : %s\n", clients[i]->name);
      write(clients[i]->fd, my_strconcat("Hej!", clients[i]->name), my_strlen(my_strconcat("Hej!", clients[i]->name)));
      write(clients[i]->fd, "\n", my_strlen("\n"));
    }
    list_chain->clients_list = clients;
  }
