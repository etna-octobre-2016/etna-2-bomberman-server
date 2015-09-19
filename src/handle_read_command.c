#include "../lib/my/src/headers/my.h"
#include "./headers/selecting.h"
#include "./headers/chain_handlers.h"
#include "./headers/map_player_actions.h"
#include "./headers/handle_read_command.h"
#include "./headers/handle_map.h"
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

t_listFunc structList[] =
  {
    {"up", function_up},
    {"down", function_down},
    {"left", function_left},
    {"right", function_right},
    {"bomb", function_bomb},
    {"update", function_update},
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
  if (client->state != IS_DEAD)
  {
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
      map_player_bomb(client);
      send_map(client);
      write(client->fd, "ko\n", my_strlen("ko\n"));
      pthread_mutex_unlock(&(client->mutex));
    }
  }
  else
  {
    write(client->fd, "dead\n", my_strlen("dead\n"));
    pthread_mutex_unlock(&(client->mutex));
  }
  free(buffer_read);
  pthread_exit(NULL);
}

void function_up(s_client* client)
{
  my_printf("OK\n");
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
void function_down(s_client* client)
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
void function_bomb(s_client* client)
{
  my_printf("OK\n");
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
void function_update(s_client* client)
{
  my_printf("OK\n");
  send_map(client);
  write(client->fd, "ok\n", my_strlen("ok\n"));
  pthread_mutex_unlock(&(client->mutex));
}
