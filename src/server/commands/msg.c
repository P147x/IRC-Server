/*
** msg.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sat Jun  3 10:52:48 2017 Lucas Debouté
** Last update Thu Jun  8 18:38:35 2017 Lucas Debouté
*/

#include "server.h"

t_client     	*client_exists(t_list *clientlist, char *nickname)
{
  t_client	*cursor;

  cursor = clientlist->begin;
  while (cursor != NULL)
    {
      if (!strcmp(cursor->nickname, nickname))
	return (cursor);
      cursor = cursor->next;
    }
  return (NULL);
}

int	chanerror(t_server *server, t_client *client,
		  char *cmd, int err, char *msg)
{
  dprintf(client->fd, ":%s!%s@%s %d %s %s\r\n",
	  client->nickname, client->nickname, server->hostname,
	  err, cmd, msg);
  return (0);
}

int	cmd_pmsg(t_server *server, t_client *client, char **cmd)
{
  char	*msg;
  int	i;

  if (cmd[1] == NULL)
    return (chanerror(server, client, cmd[0], 461, "Channel name requiered"));
  i = -1;
  while (server->lcmd[++i] != '\0' &&
	 server->lcmd[i] != ':' && server->lcmd[i] != '\r');
  if (server->lcmd[i] == '\0')
    return (0);
  if ((msg = malloc(strlen(server->lcmd) + 22 + (strlen(client->nickname) * 2)
		    + strlen(cmd[1]))) == NULL)
    return (1);
  memset(msg, 0, strlen(server->lcmd) + 22 + (strlen(client->nickname) * 2)
	 + strlen(cmd[1]));
  sprintf(msg, ":%s!%s@%s PRIVMSG %s %s", client->nickname, client->nickname,
	  server->hostname, cmd[1], strtok(&server->lcmd[i], "\r"));
  if (cmd[1][0] == '#' && chan_isjoined(&client->chanlist, cmd[1]) != NULL)
    sendto_channel(server, cmd[1], msg, client->fd);
  else if (client_exists(&server->clients, cmd[1]) != NULL)
    sendto_user(server, cmd[1], msg);
  free(msg);
  return (0);
}
