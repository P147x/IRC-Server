/*
** ringbuffer.c for myirc in /home/codeine/Projects/B4/PSU/v2/v3/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Wed Jun  7 18:21:06 2017 Lucas Debouté
** Last update Thu Jun  8 00:03:01 2017 Lucas Debouté
*/

#include "server.h"

int	init_ringbuffer(t_ringbuffer *rbuffer)
{
  if ((rbuffer->buffer = malloc(512)) == NULL)
    return (1);
  rbuffer->head = 0;
  rbuffer->tail = 0;
  return (0);
}

int	push_ringbuffer(t_ringbuffer *rbuffer, char c)
{
  int	next;

  next = rbuffer->head + 1;
  if (next >= 512)
    next = 0;
  if (next == rbuffer->tail)
    return (1);
  rbuffer->buffer[rbuffer->head] = c;
  rbuffer->head = next;
  return (0);
}

char		pop_ringbuffer(t_ringbuffer *rbuffer)
{
  int		next;
  char		tmp;

  if (rbuffer->head == rbuffer->tail)
    return ('\0');
  next = rbuffer->tail + 1;
  if (next >= 512)
    next = 0;
  tmp = rbuffer->buffer[rbuffer->tail];
  rbuffer->tail = next;
  return (tmp);
}

int		write_ringbuffer(t_ringbuffer *rbuffer, char *str)
{
  unsigned int		i;

  i = 0;
  while (str[i] != '\0')
    {
      push_ringbuffer(rbuffer, str[i]);
      i += 1;
    }
  return (0);
}

char	       *read_ringbuffer(t_ringbuffer *rbuffer)
{
  int		i;
  char			*buffer;

  i = 0;
  if ((buffer = malloc(512)) == NULL)
    return (NULL);
  memset(buffer, 0, 512);
  while ((buffer[i] = pop_ringbuffer(rbuffer)) != '\r')
  {
    i += 1;
  }
  return (buffer);
}
