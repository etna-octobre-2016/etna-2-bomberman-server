#include "../lib/my/src/headers/my.h"
#include "./headers/main.h"
#include "./headers/init_server.h"
#include "./headers/selecting.h"
#include "./headers/handle_map.h"
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


int main()
{
  init_server();
  //TODO Handle map
  //PARSE SELECT + THREAD
  init_map();
  free(map);
  handle_select(list_chain->clients_list);
  free(list_chain->clients_list);
  return (0);
}
