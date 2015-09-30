#include "../lib/my/src/headers/my.h"
#include "./headers/handler_acceptance_chaining.h"
#include "./headers/init_server.h"
#include "./headers/main.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


void          init_server()
{
  int                 listener;
  struct sockaddr_in  srv_addr;
  struct protoent     *proto;
  int                 on;
  s_server*           server_info_create;

  on = 1;
  if ((proto = getprotobyname("TCP")) == NULL)
  {
    exit(EXIT_FAILURE);
  }
  if ((listener = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
  {
    exit(EXIT_FAILURE);
  }
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = INADDR_ANY;
  srv_addr.sin_port = htons(PORT);
  //OPT TO RE-USE THE SAME PORT
  setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  if ((bind(listener, (const struct sockaddr*)&srv_addr, sizeof(srv_addr))) == -1)
  {
    exit(EXIT_FAILURE);
  }
  if ((listen(listener, BACKLOG - 1)) == -1)
  {
    my_printf("Connexion ko\n");
    exit(EXIT_FAILURE);
  }
  my_printf("Connexion ok\n");
  //Function Handle acceptance + create chain per client
  handler_acceptance_chaining(listener);
  my_printf("Connexion ok\n");
  if ((server_info_create = malloc(sizeof(s_server))) == NULL)
  {
    exit(EXIT_FAILURE);
  };
  server_info_create->listener = listener;
  list_chain->server_info = server_info_create;
}
