/*
** handler.c for myirc in /home/codeine/crashtest/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun Jun 11 19:23:21 2017 Lucas Debouté
** Last update Sun Jun 11 22:36:55 2017 Lucas Debouté
*/

#include "client.h"

int		handle_chan(char *cmd, t_client *client)
{
  char		**tab;
  int		i;

  if (strlen(cmd) <= 5)
    return (0);
  i = 4;
  while (cmd[i++] != '\0' && cmd[i] == ' ');
  if (cmd[i] == '\0')
    return (0);
  tab = str_to_wordtab(cmd);
  if (client->channame != NULL)
    printf("[Client] Already connected to a channel\n");
  else if (tab[1] != NULL)
    {
      client->channame = strdup(tab[1]);
      dprintf(client->server_fd, "JOIN %s\r\n", tab[1]);
    }
  return (0);
}

int		handle_message(char *cmd, t_client *client)
{
  if (client->channame == NULL)
    printf("[Client] Not connected to any channel !\n");
  else
    {
      dprintf(client->server_fd, "PRIVMSG %s :%s\r\n",
	      client->channame, cmd);
    }
  return (0);
}

int		handle_part(t_client *client)
{
  if (client->channame == NULL)
    printf("[Client] Not connected to any channel !\n");
  else
    {
      free(client->channame);
      client->channame = NULL;
    }
  return (0);
}

int		handle_entry(t_client *c)
{
  char		*buf;
  char		bis[512];
  unsigned int	i;

  i = 0;
  bzero(bis, 512);
  if ((buf = get_next_line(0)) == NULL)
    return (1);
  if (strcmp(buf, "") && strstr(buf, "/join") != NULL)
    handle_chan(buf, c);
  else if (strcmp(buf, "") && buf[0] == '/')
    {
      if (strcmp(buf, "") && strstr(buf, "/part") != NULL)
	handle_part(c);
      while (buf[i++] != ' ' && buf[i] != '\0')
	bis[i - 1] = toupper(buf[i]);
      i -= 1;
      while (buf[i++] != '\0')
	bis[i - 1] = buf[i];
      dprintf(c->server_fd, "%s\r\n", bis);
    }
  else
    handle_message(buf, c);
  return (0);
}

