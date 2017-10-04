/*
** server.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc/src/server
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sat May 27 15:14:52 2017 Lucas Debouté
** Last update Sun Jun 11 22:58:36 2017 Lucas Debouté
*/

#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include "server.h"

void	handle_disconnect(int sig)
{
  UNUSED(sig);
  printf("[Server] SIGINT Catched !\n");
  printf("[Server] Destruction of server asked.\n");
}

int	which_isset(t_server *server)
{
  t_client	*curs;

  curs = server->clients.begin;
  while (curs != NULL)
    {
      if (FD_ISSET(curs->fd, &server->lfd))
	{
	  recv_client(server, curs);
	  return (0);
	}
      else if (FD_ISSET(curs->fd, &server->wfd))
	{
	  recv_client(server, curs);
	  return (0);
	}
      curs = curs->next;
    }
  return (1);
}

int		destruct_server(t_server *server)
{
  t_client	*client;

  client = server->clients.begin;
  while (client != NULL)
    {
      free_userchanlist(&client->chanlist);
      client = client->next;
    }
  free_chanlist(&server->channels);
  free_llist(&server->clients);
  return (0);
}

int		run_server(t_server *server)
{
  signal(SIGINT, handle_disconnect);
  while (1)
    {
      update_clients(server);
      if (server->gfd == server->fd)
	init_select(server);
      if (select(server->gfd + 1, &server->lfd, &server->wfd, NULL,
		 NULL) == -1)
	return (0);
      if (FD_ISSET(server->fd, &server->lfd))
	add_client(server);
      else
	which_isset(server);
    }
  return (0);
}

int		main(int argc, char **argv)
{
  t_server	server;

  server.port = check_args(argc, argv);
  if (server.port == 0 || server.port == 1)
    return (server.port);
  if (init_server(&server) == 1)
    return (1);
  init_ringbuffer(&server.buffer);
  init_llist(&server.clients);
  init_chan_list(&server.channels);
  init_select(&server);
  run_server(&server);
  destruct_server(&server);
  return (0);
}
