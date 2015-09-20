#include "../lib/my/src/headers/my.h"
#include "./headers/chain_handlers.h"
#include "./headers/handler_acceptance_chaining.h"
#include "./headers/main.h"
#include "./headers/handle_map.h"
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

void          client_chain_handler_init()
{
  s_client*     client;

  list_chain = malloc(sizeof(s_listChain));
  client = malloc(sizeof(s_client));
  if ((list_chain == NULL) || (client == NULL))
  {
    exit(EXIT_FAILURE);
  }
  client->next = NULL;
  list_chain->first = client;
}

s_client*     add_client()
{
  s_client*     client;

  if((client = malloc(sizeof(s_client))) == NULL)
  {
    exit(EXIT_FAILURE);
  }
  client->next = list_chain->first;
  list_chain->first = client;
  return (client);
}

void add_clients_list(s_client** clients)
{
    list_chain->clients_list = clients;
}

void kill_player(int map_id)
{
  s_client* client;

  client = list_chain->first;
  while(client != NULL)
  {
    if (client->map_id == map_id)
    {
      client->state = IS_DEAD;
    }
    client = client->next;
  }
}

void deleteAllChain()
{
  s_client* client;

  while (list_chain->first != NULL)
    {
      client = list_chain->first;
      list_chain->first = client->next;
      free(client);
    }
  free(list_chain);
}
