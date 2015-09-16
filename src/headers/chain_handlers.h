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
  int               map_id;
  int               fd;
  int               position;
  int               state_bomb;
  int               position_bomb;
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

void   client_chain_handler_init();
s_client*   add_client();
void   add_clients_list(s_client** clients);
void regen_client_actions();
void   deleteAllChain();






#endif
