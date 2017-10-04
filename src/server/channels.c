/*
** channels.c for myirc in /home/codeine/Projects/B4/PSU/v2/v3/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Wed Jun  7 12:01:06 2017 Lucas Debouté
** Last update Thu Jun  8 16:39:51 2017 Lucas Debouté
*/

#include "server.h"

int		get_chansize(t_chanlist *chanlist, char *channel)
{
  t_channel	*curs;
  unsigned int	i;

  i = 0;
  if (chanlist->size == 0)
    return (-1);
  curs = chanlist->begin;
  while (curs != NULL &&
	 strcmp(curs->channel, channel))
    {
      curs = curs->next;
      i += 1;
    }
  if (curs != NULL)
    return (curs->users);
  return (0);
}

int		upd_chansize(t_chanlist *chanlist, char *channel, int symb)
{
  t_channel	*curs;

  if (chanlist->size == 0)
    return (-1);
  curs = chanlist->begin;
  while (curs != NULL &&
	 strcmp(curs->channel, channel))
    curs = curs->next;
  if (curs != NULL)
    {
      if (symb == 0)
	curs->users -= 1;
      else if (symb == 1)
	curs->users += 1;
    }
  return (0);
}
