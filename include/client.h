/*
** client.h for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun May 28 18:05:22 2017 Lucas Debouté
** Last update Sun Jun 11 19:37:04 2017 Lucas Debouté
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# define UNUSED(x) (void)(x)

# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/select.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "get_next_line.h"

typedef struct	s_client
{
  int		port;
  int		server_fd;
  fd_set	readfs;
  fd_set	writefs;
  char		*channame;
}		t_client;

int		create_socket();
int		check_args(int, char **);
int		run_client(t_client *client);
int		init_main(int argc, char **argv, t_client *c);
void		init_select(t_client *client);

void		handle_disconnect(int sig);
char		**str_to_wordtab(char *);

/*
** COMMAND HANDLING
*/
int		handle_chan(char *cmd, t_client *client);
int		handle_part(t_client *client);
int		handle_message(char *cmd, t_client *client);
int		handle_entry(t_client *client);

#endif /* CLIENT_H_ */
