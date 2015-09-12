#ifndef SOFTWAR_CHAINHANDLERS_H
#define SOFTWAR_CHAINHANDLERS_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
#include <pthread.h>

typedef struct            s_client
{
  char*             name;
  int               fd;
  int               action_available;
  pthread_mutex_t   mutex;
  struct s_client*  next;
}                   s_client;

typedef struct            s_listChain
{
  struct s_client*    first;
  struct s_client**   clients_list;
  struct s_server*    server_info;
}                   s_listChain;

/*GLOBAL CHAIN LIST*/
s_listChain*   list_chain;

void   client_chain_handler_init(char* client_name);
s_client*   add_client(char* client_name);
void   add_clients_list(s_client** clients);
void regen_client_actions();
void   deleteAllChain();






#endif
