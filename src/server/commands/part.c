/*
** part.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sat Jun  3 10:48:27 2017 Lucas Debouté
** Last update Thu Jun  8 18:39:38 2017 Lucas Debouté
*/

#include "server.h"

int	cmd_part(t_server *server, t_client *client, char **cmd)
{
  char	*msg;

  if (cmd[1] == NULL)
    return (chanerror(server, client, cmd[0], 461, "Channel name requiered"));
  if ((msg = malloc((strlen(client->nickname) * 2) + 19
		    + strlen(cmd[1]))) == NULL)
    return (1);
  memset(msg, 0, (strlen(client->nickname) * 2) + 19 + strlen(cmd[1]));
   if (chan_isjoined(&client->chanlist, cmd[1]) != NULL)
     {
       sprintf(msg, ":%s!%s@127.0.0.1 PART %s", client->nickname,
	       client->nickname, cmd[1]);
       sendto_channel(server, cmd[1], msg, 0);
       del_chan(&client->chanlist, cmd[1]);
       upd_chansize(&server->channels, cmd[1], 0);
       if (get_chansize(&server->channels, cmd[1]) == 0)
	 rem_chan(&server->channels, cmd[1]);
     }
   else
     dprintf(client->fd, ":%s!%s@saltirc 403 %s :Channel name requiered\r\n",
	     client->nickname, client->nickname, cmd[1]);
   free(msg);
   return (0);
}
