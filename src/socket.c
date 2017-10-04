/*
** socket.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Mon May 29 18:20:52 2017 Lucas Debouté
** Last update Wed May 31 19:18:50 2017 Noémie CARON
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

int			create_socket()
{
  int			fd;
  struct protoent	*pe;

  if (!(pe = getprotobyname("TCP")))
    {
      perror("Unable to get TCP prototype");
      return (-1);
    }
  fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (fd == -1)
    {
      perror("Unable to create a new TCP socket");
      return (-1);
    }
  return (fd);
}

int			create_queue(int fd)
{
  if (listen(fd, 1024) == -1)
    {
      perror("Unable to initializate queue");
      close(fd);
      return (1);
    }
  return (0);
}

int			create_bind(int fd, const int port)
{
  struct sockaddr_in	s_in;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *) &s_in, sizeof(s_in)) == -1)
    {
      perror("Unable to binding socket");
      close(fd);
      return (1);
    }
  return (0);
}
