/*
** quit.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  2 19:07:28 2017 Lucas Debouté
** Last update Thu Jun  8 02:14:19 2017 Lucas Debouté
*/

#include "server.h"

int	cmd_quit(t_server *server, t_client *client, char **cmd)
{
  UNUSED(cmd);
  printf("[Server] Client %d has closed connexion.\n", client->fd);
  delete_client(server, client->fd);
  return (0);
}
