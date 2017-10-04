/*
** commands.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Fri Jun  2 14:36:57 2017 Lucas Debouté
** Last update Sun Jun 11 22:58:12 2017 Lucas Debouté
*/

#include "server.h"

void	init_cmd_ptr(int (**functions)(t_server *server, t_client *, char **))
{
  functions[0] = &cmd_user;
  functions[1] = &cmd_nick;
  functions[2] = &cmd_quit;
  functions[3] = &cmd_join;
  functions[4] = &cmd_part;
  functions[5] = &cmd_ping;
  functions[6] = &cmd_pmsg;
  functions[7] = &cmd_users;
  functions[8] = &cmd_list;
  functions[9] = &cmd_names;
  functions[10] = &cmd_topic;
}

void	init_cmd_lst(char *tags[CMD_SIZE])
{
  tags[0] = "USER";
  tags[1] = "NICK";
  tags[2] = "QUIT";
  tags[3] = "JOIN";
  tags[4] = "PART";
  tags[5] = "PING";
  tags[6] = "PRIVMSG";
  tags[7] = "USERS";
  tags[8] = "LIST";
  tags[9] = "NAMES";
  tags[10] = "TOPIC";
  tags[11] = NULL;
}

int	exec_cmd(t_server *server, t_client *client, char **cmd)
{
  int	(*functions[CMD_SIZE])(t_server *server, t_client *client,
			       char **cmd);
  char	*tags[CMD_SIZE];
  int	i;

  i = 0;
  init_cmd_ptr(functions);
  init_cmd_lst(tags);
  while (tags[i] != NULL && strcmp(cmd[0], tags[i]))
    i += 1;
  if (tags[i] == NULL)
    return (1);
  else
    if ((*functions[i])(server, client, cmd) == 1)
      return (1);
  return (0);
}
