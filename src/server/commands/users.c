/*
** users.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun Jun  4 17:43:51 2017 Lucas Debouté
** Last update Thu Jun  8 18:41:54 2017 Lucas Debouté
*/

#include "server.h"

int	cmd_users(t_server *server, t_client *client, char **cmd)
{
  t_client	*cursor;

  UNUSED(cmd);
  if (server->clients.size == 0)
    {
      dprintf(client->fd, ":127.0.0.1 395 %s :No users\r\n", client->nickname);
      return (0);
    }
  cursor = server->clients.begin;
  dprintf(client->fd, ":127.0.0.1 392 %s :Listing users\r\n",
	  client->nickname);
  dprintf(client->fd, ":127.0.0.1 393 %s :", client->nickname);
  while (cursor != NULL)
    {
      if (cursor->nickname != NULL)
	dprintf(client->fd, "%s ", cursor->nickname);
      cursor = cursor->next;
    }
  dprintf(client->fd, "\r\n");
  dprintf(client->fd, ":127.0.0.1 394 %s :End of listing!\r\n",
	  client->nickname);
  return (0);
}
