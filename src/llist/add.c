/*
** add.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Tue May 30 20:47:16 2017 Lucas Debouté
** Last update Thu Jun  8 11:39:55 2017 Lucas Debouté
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llist.h"

char		*generate_nnick(int fd)
{
  char		nbr[255];
  char		*nick;

  sprintf(nbr, "_guest%d", fd);
  nick = strdup(nbr);
  return (nick);
}

int		add_llist(t_list *list, int fd)
{
  t_client	*elem;

  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (1);
  elem->fd = fd;
  elem->nickname = generate_nnick(fd);
  elem->welcomed = false;
  init_userchan_list(&elem->chanlist);
  elem->authentificated = false;
  if (list->size == 0)
    {
      elem->prev = list->begin;
      elem->next = list->end;
      list->begin = elem;
    }
  else if (list->size != 0)
    {
      elem->next = NULL;
      elem->prev = list->end;
      list->end->next = elem;
    }
  list->end = elem;
  list->size += 1;
  return (0);
}

int		add_chan_inlist(t_userchanlist *list, char *chan)
{
  t_userchan	*elem;

  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (1);
  elem->channel = strdup(chan);
  if (list->size == 0)
    {
      elem->prev = list->begin;
      elem->next = list->end;
      list->begin = elem;
    }
  else if (list->size != 0)
    {
      elem->next = NULL;
      elem->prev = list->end;
      list->end->next = elem;
    }
  list->end = elem;
  list->size += 1;
  return (0);
}

int		new_chan(t_chanlist *list, char *chan)
{
  t_channel	*elem;

  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (1);
  elem->channel = strdup(chan);
  elem->users = 0;
  elem->topic = NULL;
  if (list->size == 0)
    {
      elem->prev = list->begin;
      elem->next = list->end;
      list->begin = elem;
    }
  else if (list->size != 0)
    {
      elem->next = NULL;
      elem->prev = list->end;
      list->end->next = elem;
    }
  list->end = elem;
  list->size += 1;
  printf("[Server]: channel %s created.\n", chan);
  return (0);
}
