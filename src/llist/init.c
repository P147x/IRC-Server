/*
** init.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc/src/llist
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Tue May 30 20:12:58 2017 Lucas Debouté
** Last update Tue Jun  6 17:36:37 2017 Lucas Debouté
*/

#include "llist.h"

void	init_llist(t_list *list)
{
  list->size = 0;
  list->fd_max = 0;
  list->begin = NULL;
  list->end = NULL;
}

void	init_userchan_list(t_userchanlist *list)
{
  list->size = 0;
  list->begin = NULL;
  list->end = NULL;
}

void	init_chan_list(t_chanlist *list)
{
  list->size = 0;
  list->begin = NULL;
  list->end = NULL;
}
