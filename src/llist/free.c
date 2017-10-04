/*
** free.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Wed May 31 20:18:56 2017 Lucas Debouté
** Last update Sun Jun 11 22:59:12 2017 Lucas Debouté
*/

#include "server.h"

void		free_llist(t_list *list)
{
  t_client	*tmp1;
  t_client	*tmp2;

  tmp1 = list->begin;
  while (tmp1 != NULL)
    {
      tmp2 = tmp1;
      tmp1 = tmp1->next;
      free(tmp2);
    }
}

void		free_userchanlist(t_userchanlist *list)
{
  t_userchan	*tmp1;
  t_userchan	*tmp2;

  tmp1 = list->begin;
  while (tmp1 != NULL)
    {
      tmp2 = tmp1;
      tmp1 = tmp1->next;
      free(tmp2);
    }
}

void		free_chanlist(t_chanlist *list)
{
  t_channel	*tmp1;
  t_channel	*tmp2;

  tmp1 = list->begin;
  while (tmp1 != NULL)
    {
      tmp2 = tmp1;
      tmp1 = tmp1->next;
      free(tmp2);
    }
}
