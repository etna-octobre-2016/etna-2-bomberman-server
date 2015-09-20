#include "../lib/my/src/headers/my.h"
#include "./headers/selecting.h"
#include "./headers/init_server.h"
#include "./headers/threads.h"
#include "./headers/handle_read_command.h"
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>

pthread_mutex_t  mutex_read_and_actions_client1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t  mutex_read_and_actions_client2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t  mutex_read_and_actions_client3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t  mutex_read_and_actions_client4 = PTHREAD_MUTEX_INITIALIZER;

int handle_select(s_client** clients_list_all)
  {
    int                 result;
    // struct timeval      tv;
    int                 i;
    pthread_t           threads_client[BACKLOG];
    pthread_t           thread_map;
    fd_set              readfs;
    fd_set              writefs;

    //Announcing Starting Game
    for (i = 0; i < BACKLOG; i++)
    {
      if (write(clients_list_all[i]->fd, "start", my_strlen("start")) < 0)
      {
        my_printf("send()");
        exit(errno);
      }
    }
    //Debug display map /3sec
    pthread_create(&(thread_map), NULL, (void *)thread_display_map, NULL);
    while (42)
    {
      /*SET TIMEOUT AFTER 2.5 SECONDS*/
      // tv.tv_sec = 2;
      // tv.tv_usec = 500000;
      FD_ZERO(&readfs);
      FD_ZERO(&writefs);
      for (i = 0; i < BACKLOG; i++)
      {
        FD_SET(clients_list_all[i]->fd, &readfs);
      }
      for (i = 0; i < BACKLOG; i++)
      {
        FD_SET(clients_list_all[i]->fd, &writefs);
      }
      FD_SET(0, &readfs);
      result = select(8, &readfs, &writefs, NULL, NULL);
      if (result == 0)
      {
        my_printf("TIMEOUT!\n");
        result = 1;
      }
      for (i = 0; i < BACKLOG; i++)
      {
        if (FD_ISSET(clients_list_all[i]->fd, &readfs))
        {
          //Read Command from client
          pthread_mutex_lock(&(clients_list_all[i]->mutex));
          my_printf("HANDLE SELECT READ OK\n");
          pthread_create(&(threads_client[i]), NULL, (void*)handle_read_command, (void *)clients_list_all[i]);
          FD_CLR(clients_list_all[i]->fd, &readfs);
        }
        if (FD_ISSET(clients_list_all[i]->fd, &writefs))
        {
          FD_CLR(clients_list_all[i]->fd, &writefs);
        }
      }
      if (FD_ISSET(0, &readfs))
      {
        for (i = 0; i < BACKLOG; i++)
          close(clients_list_all[i]->fd);
        close(list_chain->server_info->listener);
        deleteAllChain();
        killThread(threads_client);
        pthread_kill(thread_map, 20);
        exit(EXIT_SUCCESS);
      }
    }
  }
