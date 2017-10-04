/*
** topic.c for myirc in /home/codeine/Projects/B4/PSU/v2/v3/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Wed Jun  7 14:07:38 2017 Lucas Debouté
** Last update Sun Jun 11 23:35:00 2017 Lucas Debouté
*/

#include "server.h"

char		*get_topic(t_chanlist *chanlist, char *channel)
{
  t_channel	*chan;

  if (chanlist->size == 0)
    return (NULL);
  chan = chanlist->begin;
  while (chan != NULL)
    {
      if (!strcmp(chan->channel, channel))
	return (chan->topic);
      chan = chan->next;
    }
  return (NULL);
}

int		set_topic(t_chanlist *chanlist, char *channel, char *msg)
{
  t_channel	*chan;

  if (chanlist->size == 0)
    return (1);
  chan = chanlist->begin;
  while (chan != NULL)
    {
      if (!strcmp(chan->channel, channel))
	{
	  chan->topic = strdup(msg);
	  return (0);
	}
      chan = chan->next;
    }
  return (0);
}

int	cmd_topic(t_server *server, t_client *client, char **cmd)
{
  int	i;

  if (cmd[1] != NULL && cmd[2] == NULL)
    {
      if (get_topic(&server->channels, cmd[1]) != NULL)
	dprintf(client->fd, ":%s 332 %s %s :%s\n\r", server->hostname,
		client->nickname,
		cmd[1], get_topic(&server->channels, cmd[1]));
      else
	dprintf(client->fd, ":%s 331 %s %s :No topic for %s.\n\r",
		server->hostname, client->nickname, cmd[1], cmd[1]);
    }
  else if (cmd[1] != NULL && cmd[2] != NULL)
    {
        i = -1;
	while (server->lcmd[++i] != '\0' && server->lcmd[i] != ':');
	if (server->lcmd[i] == '\0' || server->lcmd[i + 1] == '\0')
	  return (0);
	set_topic(&server->channels, cmd[1], &server->lcmd[i + 1]);
    }
  return (0);
}
