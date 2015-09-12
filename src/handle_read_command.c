#include "../lib/my/src/headers/my.h"
#include "./headers/selecting.h"
#include "./headers/chain_handlers.h"
#include "./headers/handle_read_command.h"
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

t_listFunc structList[] =
  {
    {"forward", function_forward},
    {"backward", function_backward},
    {"left", function_left},
    {"right", function_right},
    {0,0}
  };

void* handle_read_command(s_client* client)
{
  char*         buffer_read;
  int           i;
  int           function_founded;

  buffer_read = malloc(sizeof(char) * 20);
  read(client->fd, buffer_read, 20);
  //TODO Handle Error_handler
  my_printf("received : #%s#\n", buffer_read);
  for (i = 0, function_founded = 0; structList[i].action != 0; i++)
  {
    if (my_strcmp(buffer_read, structList[i].action) == 0)
    {
      function_founded = 1;
      structList[i].ptr(client);
    }
  }
  if (function_founded == 0)
  {
    write(client->fd, "ko\n", my_strlen("ko\n"));
    pthread_mutex_unlock(&(client->mutex));
  }
  free(buffer_read);
  pthread_exit(NULL);
}

void function_forward(s_client* client)
{
  my_printf("OK\n");
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
void function_backward(s_client* client)
{
  my_printf("OK\n");
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
void function_left(s_client* client)
{
  my_printf("OK\n");
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
void function_right(s_client* client)
{
  my_printf("OK\n");
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
