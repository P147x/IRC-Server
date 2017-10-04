/*
** auth.c for my_irc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  2 15:11:07 2017 Lucas Debouté
** Last update Thu Jun  8 16:46:59 2017 Lucas Debouté
*/

#include "server.h"

int	cmd_user(t_server *server, t_client *client, char **cmd)
{
  if (cmd[1] == NULL || cmd[2] == NULL ||
      cmd[3] == NULL || cmd[4] == NULL)
    {
      dprintf(client->fd, ":%s 461 USER :More parameters are requiered\r\n",
	      server->hostname);
    }
  if (!client->authentificated)
    {
      if (client->nickname)
	free(client->nickname);
      client->nickname = strdup(cmd[1]);
      client->authentificated = true;
    }
  else
    dprintf(client->fd, ":%s 462 :Already registered !\r\n",
    server->hostname);
  if (!client->welcomed)
    {
      dprintf(client->fd, ":saltirc 001 %s :Welcome to SaltIRC !\r\n",
	      client->nickname);
      client->welcomed = true;
    }
  return (0);
}
