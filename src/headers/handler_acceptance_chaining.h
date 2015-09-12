#ifndef SOFTWAR_ACCEPTANCE_H
#define SOFTWAR_ACCEPTANCE_H
#include <sys/socket.h>
#include "./chain_handlers.h"


///////////////////////////////////////////////////////
// STRUCTURES
///////////////////////////////////////////////////////

typedef struct            s_acceptance_data
{
  int                 listener;
  struct sockaddr_in* cli_addr;
  socklen_t           socklen;
  pthread_mutex_t*    mutex;
  s_client*           client;
}                   s_acceptance_data;

///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////

void handler_acceptance_chaining(int listener);

#endif
