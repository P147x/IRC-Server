/*
** scrutter.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun May 28 17:21:41 2017 Lucas Debouté
** Last update Sun Jun 11 23:33:08 2017 Lucas Debouté
*/

#include "server.h"

int		derror(char *str)
{
  write(2, "[Error] ", 8);
  write(2, str, strlen(str));
  write(2, "\n", 2);
  return (1);
}

int		is_number(char *nbr)
{
  unsigned int	i;

  i = 0;
  while (nbr[i] != '\0')
    {
      if (nbr[i] < '0' || nbr[i] > '9')
	return (0);
      i += 1;
    }
  return (1);
}

int		check_args_server(int argc, char **argv)
{
  int		port;

  if (argc != 2)
    return (derror("One argument is required. Type \"--help\" for usage."));
  if (!is_number(argv[1]))
    {
      if (!strcmp(argv[0], "./server") &&
	  !strcmp(argv[1], "--help"))
	server_usage();
      else
	return (derror("Port must be a number. Use --help for tips"));
    }
  else
    {
      port = atoi(argv[1]);
      if (port <= 1 || port > 65535)
	return (derror("Port is out of range (must be between 0 and 65535)"));
      return (port);
    }
  return (0);
}

int		check_args_client(int argc, char **argv)
{
  int		port;

  if (argc == 2)
    {
      if (!strcmp(argv[0], "./client") &&
	  !strcmp(argv[1], "--help"))
	client_usage();
      else
	return (derror("Two arguments are required. Type \"--help\" for usage."));
      return (1);
    }
  if (argc != 3)
    return (derror("Two arguments are required. Type \"--help\" for usage."));
  if (!is_number(argv[2]))
    return (derror("Port must be a number. Use --help for tips"));
  else
    {
      port = atoi(argv[2]);
      if (port <= 1 || port > 65535)
	return (derror("Port is out of range (must be between 0 and 65535)"));
      return (port);
    }
  return (0);
}

int		check_args(int argc, char **argv)
{
  if (!strcmp(argv[0], "./server"))
    return (check_args_server(argc, argv));
  else
    return (check_args_client(argc, argv));
}
