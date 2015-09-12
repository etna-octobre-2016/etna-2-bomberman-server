#ifndef SOFTWAR_HANDLE_READ_H
#define SOFTWAR_HANDLE_READ_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

#include "./chain_handlers.h"

typedef struct structFunction
{
  char *action;
  void (*ptr)(s_client*);
}t_listFunc;

///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
void* handle_read_command(s_client* client);
void function_forward();
void function_backward(s_client* client);
void function_left(s_client* client);
void function_right(s_client* client);

#endif
