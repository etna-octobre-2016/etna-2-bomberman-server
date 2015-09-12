#include "../lib/my/src/headers/my.h"
#include "./headers/chain_handlers.h"
#include "./headers/handler_acceptance_chaining.h"
#include "./headers/main.h"
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

void          client_chain_handler_init(char* client_name)
{
  s_client*     client;

  list_chain = malloc(sizeof(s_listChain));
  client = malloc(sizeof(s_client));
  if ((list_chain == NULL) || (client == NULL))
  {
    exit(-1);
  }
  client->name = client_name;
  client->action_available = 0;
  list_chain->first = client;
}

s_client*     add_client(char* client_name)
{
  s_client*     client;

  client = malloc(sizeof(s_client));
  client->name = client_name;
  client->action_available = 0;
  client->next = NULL;
  list_chain->first->next = client;
  return (client);
}

void add_clients_list(s_client** clients)
{
    list_chain->clients_list = clients;
}

void regen_client_actions()
{
  s_client* entity;

  entity = list_chain->first;
  while(entity != NULL)
  {
    entity->action_available = 1;
    entity = entity->next;
  }
}

void deleteAllChain()
{
  s_client* entity;

  while (list_chain->first != NULL)
    {
      entity = list_chain->first;
      list_chain->first = entity->next;
      free(entity);
    }
  free(list_chain);
}
