/*
** set_cfd.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Wed May 31 22:21:00 2017 Lucas Debouté
** Last update Thu Jun  1 13:32:03 2017 Lucas Debouté
*/

#include "server.h"

void		set_gfd(t_server *server)
{
  t_client	*tmp;
  int		mfd;

  mfd = server->fd;
  tmp = server->clients.begin;
  while (tmp != NULL)
    {
      if (tmp->fd > mfd)
	mfd = tmp->fd;
      tmp = tmp->next;
    }
  server->gfd = mfd;
}
