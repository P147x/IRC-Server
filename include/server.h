/*
** server.h for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun May 28 18:00:05 2017 Lucas Debouté
** Last update Thu Jun  8 18:39:08 2017 Lucas Debouté
*/

#ifndef SERVER_H_
# define SERVER_H_

# define UNUSED(x) (void)(x)
# define CMD_SIZE 12

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "llist.h"

enum		e_fdtype
  {
    FREE,
    CLIENT,
    SERVER
  }			;

typedef struct	s_ringbuffer
{
  char		*buffer;
  int		head;
  int	        tail;
}		t_ringbuffer;

typedef struct	s_server
{
  int		fd;
  int		gfd;
  fd_set	lfd;
  fd_set	wfd;
  unsigned int 	port;
  char		*hostname;
  char		*lcmd;
  t_ringbuffer	buffer;
  t_list	clients;
  t_chanlist	channels;
}		t_server;

/*
** INITIALIZATION
*/

int	check_args(int argc, char **argv);
void	server_usage();
void	client_usage();
int	create_socket();
int	create_queue();
int	create_bind();
void	init_select(t_server *server);
int	init_server(t_server *server);

/*
** CLIENT HANDLING
*/

int	add_client(t_server *server);
int	delete_client(t_server *server, int fd);
void	set_gfd(t_server *server);
int	recv_client(t_server *server, t_client *client);
void	update_clients(t_server *server);

/*
** TOOLS
*/

char	**str_to_wordtab(char *str);
int	array_unallocation(char **array);

/*
** COMMANDS HANDLING
*/

int	exec_cmd(t_server *server, t_client *client, char **cmd);
int	cmd_user(t_server *server, t_client *client, char **cmd);
int	cmd_nick(t_server *server, t_client *client, char **cmd);
int	cmd_quit(t_server *server, t_client *client, char **cmd);
int	cmd_join(t_server *server, t_client *client, char **cmd);
int	cmd_part(t_server *server, t_client *client, char **cmd);
int	cmd_ping(t_server *server, t_client *client, char **cmd);
int	cmd_pmsg(t_server *server, t_client *client, char **cmd);
int	cmd_users(t_server *server, t_client *client, char **cmd);
int	cmd_list(t_server *server, t_client *client, char **cmd);
int	cmd_names(t_server *server, t_client *client, char **cmd);
int	cmd_topic(t_server *server, t_client *client, char **cmd);

int	sendto_channel(t_server *server, char *channel, char *msg, int sender);
int	sendto_user(t_server *server, char *user, char *msg);

/*
** CHANNELS HANDLING
*/

void	init_chan_list(t_chanlist *list);
int	add_chan_inlist(t_userchanlist *list, char *chan);
int	new_chan(t_chanlist *list, char *chan);
t_userchan     	*chan_isjoined(t_userchanlist *chanlist, char *channel);
int	del_chan(t_userchanlist *list, char *channel);
int	rem_chan(t_chanlist *list, char *channel);
int	get_chansize(t_chanlist *chanlist, char *channel);
int	upd_chansize(t_chanlist *chanlist, char *channel, int symb);
char	*get_topic(t_chanlist *chanlist, char *channel);
int	chanerror(t_server *server, t_client *client,
		  char *cmd, int err, char *msg);

/*
** RING BUFFER FUNCTIONS
*/

int	init_ringbuffer(t_ringbuffer *rbuffer);
int	push_ringbuffer(t_ringbuffer *rbuffer, char c);
char	pop_ringbuffer(t_ringbuffer *rbuffer);
int	write_ringbuffer(t_ringbuffer *rbuffer, char *str);
char*	read_ringbuffer(t_ringbuffer *rbuffer);

#endif /* SERVER_H_ */
