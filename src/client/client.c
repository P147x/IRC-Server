/*
** client.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc/src/client
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sat May 27 15:16:11 2017 Lucas Debouté
** Last update Sun Jun 11 19:25:26 2017 Lucas Debouté
*/

#include "client.h"
#include "get_next_line.h"

int		run_client(t_client *c)
{
  char		*buf;

  signal(SIGINT, handle_disconnect);
  while (1)
    {
      init_select(c);
      if (select(c->server_fd + 1, &c->readfs, &c->writefs, NULL, NULL) == -1)
	return (0);
      if (FD_ISSET(c->server_fd, &c->readfs) == 1)
	{
	  if ((buf = get_next_line(c->server_fd)) == NULL)
	    {
	      printf("[Client] Server closed connection\n");
	      return (0);
	    }
	  printf("[Server] %s\n", buf);
	}
      else if (FD_ISSET(0, &c->readfs) == 1)
	if (handle_entry(c) == 1)
	  return (0);
    }
  return (0);
}

int		main(int argc, char **argv)
{
  t_client	c;

  if (init_main(argc, argv, &c) == 1)
    return (1);
  run_client(&c);
  printf("[Client] Quit\n");
  dprintf(c.server_fd, "QUIT\r\n");
  if (close(c.server_fd) == -1)
    {
      perror("Unable to close client fd");
      return (1);
    }
  printf("[Client] Client closed.\n");
  return (0);
}
