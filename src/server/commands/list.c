/*
** list.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun Jun  4 20:39:13 2017 Lucas Debouté
** Last update Thu Jun  8 16:50:16 2017 Lucas Debouté
*/

#include "server.h"

int	fetch_list(t_userchanlist *chanlist, t_chanlist *channels,
		   char *curmsg,
		   t_client *client)
{
  t_userchan	*cursor;

  cursor = chanlist->begin;
  while (cursor != NULL)
    {
      if (strstr(curmsg, cursor->channel) == NULL)
	{
	  strcat(curmsg, cursor->channel);
	  strcat(curmsg, " ");
	  dprintf(client->fd, ":127.0.0.1 322 %s %s %d :%s\r\n",
		  client->nickname, cursor->channel,
		  get_chansize(channels, cursor->channel),
		  get_topic(channels, cursor->channel));
	}
      cursor = cursor->next;
    }
  return (0);
}

int	cmd_list(t_server *server, t_client *client, char **cmd)
{
  t_client	*cursor;
  char		*msg;

  UNUSED(cmd);
  if (server->clients.size == 0)
    return (0);
  msg = malloc(4096);
  memset(msg, 0, 4096);
  cursor = server->clients.begin;
  dprintf(client->fd, ":127.0.0.1 321 %s :Listing..\r\n", client->nickname);
  while (cursor != NULL)
    {
      fetch_list(&cursor->chanlist, &server->channels, msg, client);
      cursor = cursor->next;
    }
  strcat(msg, "\r\n");
  dprintf(client->fd, ":127.0.0.1 323 %s :End listing\r\n", client->nickname);
  return (0);
}
