/*
** send_msg.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  2 14:02:43 2017 Lucas Debouté
** Last update Thu Jun  8 16:41:10 2017 Lucas Debouté
*/

#include "server.h"

int		sendto_channel(t_server *server, char *channel,
			       char *msg, int sender)
{
  t_client	*client;

  if (server->clients.size == 0)
    return (0);
  client = server->clients.begin;
  while (client != NULL)
    {
      if (chan_isjoined(&client->chanlist, channel) != NULL &&
	  sender != client->fd)
	dprintf(client->fd, "%s\r\n", msg);
      client = client->next;
    }
  return (0);
}

int		sendto_user(t_server *server, char *user, char *msg)
{
  t_client	*client;

  if (server->clients.size == 0)
    return (0);
  client = server->clients.begin;
  while (client != NULL)
    {
      if (client->nickname != NULL &&
	  !strcmp(client->nickname, user))
	{
	  dprintf(client->fd, "%s\r\n", msg);
	  return (0);
	}
      client = client->next;
    }
  return (1);
}
