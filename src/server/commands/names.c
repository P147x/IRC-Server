/*
** names.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun Jun  4 20:39:28 2017 Lucas Debouté
** Last update Thu Jun  8 16:52:41 2017 Lucas Debouté
*/

#include "server.h"

int	cmd_names(t_server *server, t_client *client, char **cmd)
{
  t_client	*cursor;
  int		i;

  i = 0;
  if (cmd[1] == NULL || server->clients.size == 0)
    return (0);
  cursor = server->clients.begin;
  while (cursor != NULL)
    {
      if (cursor->channel != NULL &&
	  !strcmp(cursor->channel, cmd[1]))
	{
	  if (i == 0)
	    dprintf(client->fd, ":127.0.0.1 353 %s : %s: ",
		    client->nickname, cmd[1]);
	  i++;
	  dprintf(client->fd, "%s ", cursor->nickname);
	}
      cursor = cursor->next;
    }
  if (i > 0)
    dprintf(client->fd, "\n\r");
  dprintf(client->fd, ":127.0.0.1 366 %s %s End of listing\r\n",
	  client->nickname, cmd[1]);
  return (0);
}
