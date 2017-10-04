/*
** initialization.c for myirc in /home/codeine/Projects/B4/PSU/v2/v3/PSU_2016_myirc/src/client
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  9 14:02:56 2017 Lucas Debouté
** Last update Sun Jun 11 16:58:50 2017 Lucas Debouté
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void	handle_disconnect(int sig)
{
  UNUSED(sig);
  printf("[Server] SIGINT Catched !\n");
  printf("[Server] Destruction of server asked.\n");
}

int			init_main(int argc, char **argv, t_client *c)
{
  struct sockaddr_in	s_in;

  c->channame = NULL;
  if (check_args(argc, argv) == 1)
    return (1);
  c->port = atoi(argv[2]);
  if ((c->server_fd = create_socket()) == -1)
    return (1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(c->port);
  s_in.sin_addr.s_addr = inet_addr(argv[1]);
  if (connect(c->server_fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      perror("Unable to connect the fd");
      if (close(c->server_fd) == -1)
	{
	  perror("Unable to close client fd");
	  return (1);
	}
      return (1);
    }
  dprintf(c->server_fd, "USER nick 0 * :realname\r\n");
  return (0);
}

void			init_select(t_client *c)
{
  FD_ZERO(&c->readfs);
  FD_ZERO(&c->writefs);
  FD_SET(c->server_fd, &c->readfs);
  FD_SET(0, &c->readfs);
}
