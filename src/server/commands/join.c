/*
** join.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sat Jun  3 00:04:53 2017 Lucas Debouté
** Last update Thu Jun  8 16:49:24 2017 Lucas Debouté
*/

#include "server.h"

t_userchan     	*chan_isjoined(t_userchanlist *chanlist, char *channel)
{
  t_userchan	*cursor;

  cursor = chanlist->begin;
  while (cursor != NULL)
    {
      if (!strcmp(cursor->channel, channel))
	return (cursor);
      cursor = cursor->next;
    }
  return (NULL);
}

t_channel     	*chan_iscreated(t_chanlist *chanlist, char *channel)
{
  t_channel	*cursor;

  cursor = chanlist->begin;
  while (cursor != NULL)
    {
      if (!strcmp(cursor->channel, channel))
	return (cursor);
      cursor = cursor->next;
    }
  return (NULL);
}

int	cmd_join(t_server *server, t_client *client, char **cmd)
{
  char	*msg;

  if (cmd[1] == NULL)
    {
      dprintf(client->fd, ":%s!%s@%s 461 %s Channel name requiered\r\n",
	      client->nickname, client->nickname, server->hostname, cmd[0]);
      return (0);
    }
  if ((msg = malloc((strlen(client->nickname) * 2) + 19
		    + strlen(cmd[1])))== NULL)
    return (1);
  memset(msg, 0, 1 + (strlen(client->nickname) * 2) + 18 + strlen(cmd[1]));
  if (chan_isjoined(&client->chanlist, cmd[1]) == NULL)
    {
      sprintf(msg, ":%s JOIN %s", client->nickname,
	  cmd[1]);
      add_chan_inlist(&client->chanlist, cmd[1]);
      if (chan_iscreated(&server->channels, cmd[1]) == NULL)
	new_chan(&server->channels, cmd[1]);
      sendto_channel(server, cmd[1], msg, 0);
    }
  upd_chansize(&server->channels, cmd[1], 1);
  free(msg);
  return (0);
}
