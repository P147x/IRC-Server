/*
** manage_client.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Wed May 31 12:57:27 2017 Lucas Debouté
** Last update Thu Jun  8 10:43:54 2017 Lucas Debouté
*/

#include "server.h"
#include "get_next_line.h"

void		update_clients(t_server *server)
{
  t_client	*tmp;

  FD_ZERO(&server->lfd);
  server->lcmd = NULL;
  FD_SET(server->fd, &server->lfd);
  tmp = server->clients.begin;
  while (tmp != NULL)
    {
      FD_SET(tmp->fd, &server->lfd);
      tmp = tmp->next;
    }
}

int			recv_client(t_server *server, t_client *client)
{
  char			*buffer;
  char			**tab;

  if ((buffer = get_next_line(client->fd)) != NULL)
    {
      write_ringbuffer(&server->buffer, buffer);
      buffer = read_ringbuffer(&server->buffer);
      if (strcmp(buffer, ""))
	{
	  printf("[Client] %s\n", buffer);
	  tab = str_to_wordtab(buffer);
	  if (server->lcmd)
	    free(server->lcmd);
	  server->lcmd = strdup(buffer);
	  exec_cmd(server, client, tab);
	}
      free(buffer);
      array_unallocation(tab);
    }
  else
    delete_client(server, client->fd);
  return (0);
}

int			do_deletion(t_server *server, t_client *tmp,
				    t_client *prev, int fd)
{
  if (tmp->fd == fd && tmp == server->clients.begin)
    {
      server->clients.begin = tmp->next;
      if (server->clients.begin == NULL)
        server->clients.end = NULL;
      else
        server->clients.begin->prev = NULL;
    }
  else if (tmp->fd == fd && tmp == server->clients.end)
    {
      server->clients.end = prev;
      prev->next = NULL;
    }
  else if (tmp->fd == fd)
    prev->next = tmp->next;
  else
    return (1);
  return (0);
}

int			delete_client(t_server *server, int fd)
{
  t_client		*tmp;
  t_client		*prev;

  if (server->clients.size == 0)
    return (1);
  tmp = server->clients.begin;
  while (tmp != NULL && tmp->fd != fd)
    {
      prev = tmp;
      tmp = tmp->next;
    }
  if (do_deletion(server, tmp, prev, fd) == 1)
    return (1);
  free(tmp);
  server->clients.size -= 1;
  FD_CLR(fd, &server->lfd);
  close(fd);
  set_gfd(server);
  if (server->clients.size == 0)
    init_llist(&server->clients);
  return (0);
}

int			add_client(t_server *server)
{
  int			cfd;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  printf("[Server] Accepting client\n");
  client_sin_len = sizeof(client_sin);
  cfd = accept(server->fd, (struct sockaddr *)&client_sin, &client_sin_len);
  if (cfd == -1)
    {
      perror("Unable to accept new entering client");
      return (1);
    }
  FD_SET(cfd, &server->lfd);
  add_llist(&server->clients, cfd);
  set_gfd(server);
  return (0);
}
