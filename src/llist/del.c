/*
** del.c for myirc in /home/codeine/Projects/B4/PSU/v2/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Mon Jun  5 20:50:47 2017 Lucas Debouté
** Last update Wed Jun  7 12:06:39 2017 Lucas Debouté
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

int	do_userdelchan(t_userchanlist *list, t_userchan *tmp,
		   t_userchan *prev, char *channel)
{
  if (tmp == NULL)
    return (1);
  if (!strcmp(tmp->channel, channel) && tmp == list->begin)
    {
      list->begin = tmp->next;
      if (list->begin == NULL)
        list->end = NULL;
      else
        list->begin->prev = NULL;
    }
  else if (!strcmp(tmp->channel, channel) && tmp == list->end)
    {
      list->end = prev;
      prev->next = NULL;
    }
  else if (!strcmp(tmp->channel, channel))
    prev->next = tmp->next;
  else
    {
      return (1);
    }
  return (0);
}

int	del_chan(t_userchanlist *list, char *channel)
{
  t_userchan		*tmp;
  t_userchan		*prev;

  if (list->size == 0)
    return (1);
  tmp = list->begin;
  while (tmp != NULL && strcmp(tmp->channel, channel))
    {
      printf("%s\n", tmp->channel);
      prev = tmp;
      tmp = tmp->next;
    }
  printf("?\n");
  if (do_userdelchan(list, tmp, prev, channel) == 1)
    return (1);
  printf("deletion..\n");
  free(tmp);
  list->size -= 1;
  return (0);
}

int	do_delchan(t_chanlist *list, t_channel *tmp,
		   t_channel *prev, char *channel)
{
  if (tmp == NULL)
    return (1);
  if (!strcmp(tmp->channel, channel) && tmp == list->begin)
    {
      list->begin = tmp->next;
      if (list->begin == NULL)
        list->end = NULL;
      else
        list->begin->prev = NULL;
    }
  else if (!strcmp(tmp->channel, channel) && tmp == list->end)
    {
      list->end = prev;
      prev->next = NULL;
    }
  else if (!strcmp(tmp->channel, channel))
    prev->next = tmp->next;
  else
    {
      return (1);
    }
  return (0);
}

int	rem_chan(t_chanlist *list, char *channel)
{
  t_channel		*tmp;
  t_channel		*prev;

  if (list->size == 0)
    return (1);
  tmp = list->begin;
  while (tmp != NULL && strcmp(tmp->channel, channel))
    {
      printf("%s\n", tmp->channel);
      prev = tmp;
      tmp = tmp->next;
    }
  if (do_delchan(list, tmp, prev, channel) == 1)
    return (1);
  free(tmp);
  list->size -= 1;
  printf("[Server]: channel %s deleted\n", channel);
  return (0);
}
