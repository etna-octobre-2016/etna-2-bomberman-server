#include "../lib/my/src/headers/my.h"
#include "./headers/main.h"
#include "./headers/init_server.h"
#include "./headers/selecting.h"
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


int main()
{
  s_client**          clients_list_all;

  init_server();
  clients_list_all = list_chain->clients_list;
  //PARSE SELECT + THREAD
  handle_select(clients_list_all);
  free(clients_list_all);
  return (0);
}
