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
#include <stdint.h>
#include <arpa/inet.h>
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
  // i = my_strlen(buffer_read);
  // buffer_read[i - 2] = '\0';
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
  int return_value;

  my_printf("OK\n");
  return_value = map_player_up(client);
  if (return_value)
  {
    write(client->fd, "ok\n", my_strlen("ok\n"));
  }
  else
  {
    write(client->fd, "ko\n", my_strlen("ko\n"));
  }
  pthread_mutex_unlock(&(client->mutex));
}
void function_down(s_client* client)
{
  int return_value;

  my_printf("OK\n");
  return_value = map_player_down(client);
  if (return_value)
  {
    write(client->fd, "ok\n", my_strlen("ok\n"));
  }
  else
  {
    write(client->fd, "ko\n", my_strlen("ko\n"));
  }
  pthread_mutex_unlock(&(client->mutex));
}
void function_left(s_client* client)
{
  int return_value;

  my_printf("OK\n");
  return_value = map_player_left(client);
  if (return_value)
  {
    write(client->fd, "ok\n", my_strlen("ok\n"));
  }
  else
  {
    write(client->fd, "ko\n", my_strlen("ko\n"));
  }
  pthread_mutex_unlock(&(client->mutex));
}
void function_right(s_client* client)
{
  int return_value;

  my_printf("OK\n");
  return_value = map_player_right(client);
  if (return_value)
  {
    write(client->fd, "ok\n", my_strlen("ok\n"));
  }
  else
  {
    write(client->fd, "ko\n", my_strlen("ko\n"));
  }
  pthread_mutex_unlock(&(client->mutex));
}
void function_bomb(s_client* client)
{
  int return_value;

  my_printf("OK\n");
  return_value = map_player_bomb(client);
  if (return_value)
  {
    write(client->fd, "ok\n", my_strlen("ok\n"));
  }
  else
  {
    write(client->fd, "ko\n", my_strlen("ko\n"));
  }
  pthread_mutex_unlock(&(client->mutex));
}
void function_update(s_client* client)
{
  send_map(client);
  pthread_mutex_unlock(&(client->mutex));
}

char* convIntChar(int data)
{
  if (data == SYMBOL_VOID)
    return("0");
  if (data == SYMBOL_WALL_DESTRUCTIBLE)
    return("11");
  if (data == SYMBOL_WALL_INDESTRUCTIBLE)
    return("10");
  if (data == SYMBOL_BOMB_IDLE)
    return("13");
  if (data == SYMBOL_BOMB_IGNITION)
    return("14");
  if (data == 2)
    return("2");
  if (data == 3)
    return("3");
  if (data == 4)
    return("4");
  if (data == 5)
    return("5");
  if (data == 6)
    return("6");
  if (data == 7)
    return("7");
  if (data == 8)
    return("8");
  if (data == 9)
    return("9");
  return("ko");
}
