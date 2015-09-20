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
  init_map();
  handle_select(list_chain->clients_list);
  free(list_chain->clients_list);
  free(map);
  return (0);
}
