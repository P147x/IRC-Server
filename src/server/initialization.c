/*
** initialization.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  2 21:48:48 2017 Lucas Debouté
** Last update Wed Jun  7 17:32:39 2017 Lucas Debouté
*/

#include "server.h"

void	init_select(t_server *server)
{
  server->gfd = server->fd;
  FD_ZERO(&server->lfd);
  FD_ZERO(&server->wfd);
  FD_SET(server->fd, &server->lfd);
}

int	init_server(t_server *server)
{
  server->hostname = strdup("SaltIRC");
  if ((server->fd = create_socket()) == -1)
    return (1);
  if (create_bind(server->fd, server->port) == 1)
    return (1);
  if (create_queue(server->fd) == 1)
    return (1);
  return (0);
}

