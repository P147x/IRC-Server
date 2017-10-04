/*
** nick.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  2 17:57:11 2017 Lucas Debouté
** Last update Thu Jun  8 16:52:56 2017 Lucas Debouté
*/

#include "server.h"

int		is_nickinuse(t_server *server, char *nickname)
{
  t_client	*client;

  client = server->clients.begin;
  while (client != NULL)
    {
      if (client->nickname != NULL &&
	  !strcmp(client->nickname, nickname))
	return (1);
      client = client->next;
    }
  return (0);
}

int	cmd_nick(t_server *server, t_client *client, char **cmd)
{
  if (cmd[1] == NULL)
    {
      dprintf(client->fd, ":%s 433 :Nickname required for change name.\r\n",
	      server->hostname);
      return (0);
    }
  if (is_nickinuse(server, cmd[1]))
    {
      dprintf(client->fd, ":%s 433 %s :Nickname already in use !\r\n",
	      server->hostname, client->nickname);
      return (0);
    }
  dprintf(client->fd, ":%s NICK %s\r\n", client->nickname, cmd[1]);
  if (client->nickname)
    free(client->nickname);
  client->nickname = strdup(cmd[1]);
  if (!client->welcomed)
    {
      dprintf(client->fd, ":saltirc 001 %s :Welcome to SaltIRC !\r\n",
	      client->nickname);
      client->welcomed = true;
    }
  return (0);
}
