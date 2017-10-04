/*
** str_to_wordtab.c for myftp in /home/codeine/Projects/B4/PSU/PSU_2016_myftp/src
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Tue May 16 17:14:08 2017 Lucas Debouté
** Last update Mon Jun  5 22:46:24 2017 Lucas Debouté
*/

#include "server.h"

char		**array_allocation(char *str)
{
  int	i;
  int	column;
  int	size;
  char	**array;

  i = 0;
  size = 0;
  column = 0;
  array = malloc(sizeof(*array) * strlen(str) * 100);
  while (str[i] != '\0' && str[i] != '\n' && str[i] != '\r')
    {
      if (str[i] == ' ')
	{
	  array[column] = malloc((sizeof(array) + 2) * (size + 1024));
	  column++;
	  size = 0;
	}
      size += 1;
      i += 1;
    }
  column++;
  array[column] = malloc((sizeof(array) + 2) * (size + 1));
  return (array);
}

char		**str_to_wordtab(char *str)
{
  char		**tab;
  unsigned int	cursor;
  unsigned int	y;
  unsigned int	i;

  cursor = i = y = 0;
  tab = malloc((sizeof(*tab) * strlen(str) + 1) * 100);
  tab[cursor] = malloc((sizeof(tab) + 2) * (1024));
  while (str[i] != '\0' && str[i] != '\n' && str[i] != '\r')
  {
    if (str[i] == ' ')
      {
	cursor += 1;
	y = 0;
	i += 1;
	tab[cursor] = malloc((sizeof(tab) + 2) * (1024));
      }
    tab[cursor][y] = str[i];
    tab[cursor][y + 1] = '\0';
    y += 1;
    i += 1;
  }
  tab[cursor + 1] = NULL;
  return (tab);
}

int		array_unallocation(char **array)
{
  unsigned int	i;

  if (array == NULL)
    return (0);
  i = 0;
  while (array[i] != NULL)
    {
      free(array[i]);
      i += 1;
    }
  free(array);
  return (0);
}
