/*
** get_next_line.h for get_next_line in /home/debout_l/rendu/CPE_2015_getnextline
** 
** Made by Lucas DEBOUTE
** Login   <debout_l@epitech.net>
** 
** Started on  Thu Jan 14 04:30:39 2016 Lucas DEBOUTE
** Last update Thu Jun  8 00:06:02 2017 Lucas Debouté
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (512)
# endif /* READ_SIZE */

typedef struct	s_gnl
{
  int		i;
  int		boool;
  int		fd;
  unsigned int	size;
  char		*str;
}		t_gnl;

char	*get_next_line(const int fd);

#endif /* READ_SIZE */
