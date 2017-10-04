/*
** llist.h for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Tue May 30 20:24:32 2017 Lucas Debouté
** Last update Thu Jun  8 11:39:10 2017 Lucas Debouté
*/

#ifndef LLIST_H_
# define LLIST_H_

# include <stdlib.h>
# include <stdbool.h>

typedef struct		s_channel
{
  char			*channel;
  char			*topic;
  int			users;
  struct s_channel	*next;
  struct s_channel	*prev;
}			t_channel;

typedef struct		s_chanlist
{
  int			size;
  t_channel		*begin;
  t_channel		*end;
}			t_chanlist;

typedef struct		s_userchan
{
  char			*channel;
  struct s_userchan	*next;
  struct s_userchan	*prev;
}			t_userchan;

typedef struct		s_userchanlist
{
  int			size;
  t_userchan		*begin;
  t_userchan		*end;
}			t_userchanlist;

typedef struct		s_client
{
  int			fd;
  bool			authentificated;
  bool			welcomed;
  char			*nickname;
  char			*channel;
  t_userchanlist	chanlist;
  struct s_client	*next;
  struct s_client	*prev;
}			t_client;

typedef struct		s_list
{
  int			size;
  int			fd_max;
  t_client		*begin;
  t_client		*end;
}			t_list;

/*
** LLIST FUNCTIONS
*/

void	init_llist(t_list *list);
int	add_llist(t_list *list, int fd);
void	free_llist(t_list *list);
void	init_userchan_list(t_userchanlist *list);
void	free_userchanlist(t_userchanlist *list);
void	free_chanlist(t_chanlist *list);

#endif /* LLIST_H_ */
