/*
** ping.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sat Jun  3 01:35:40 2017 Lucas Debouté
** Last update Thu Jun  8 12:23:06 2017 Lucas Debouté
*/

#include "server.h"

int	cmd_ping(t_server *server, t_client *client, char **cmd)
{
  UNUSED(cmd);
  UNUSED(server);
  dprintf(client->fd, ":127.0.0.1 PONG 127.0.0.1\r\n");
  printf("[Server] PONG\n");
  return (0);
}
