#ifndef SOFTWAR_INITSERVER_H
#define SOFTWAR_INITSERVER_H

#define PORT 4242
#define BACKLOG 5
#define CYCLE_TIME 50000
#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
#include <pthread.h>

///////////////////////////////////////////////////////
// STRUCTURES
///////////////////////////////////////////////////////
typedef struct            s_server
{
  int               listener;
}                   s_server;



///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////

void           init_server();

#endif
