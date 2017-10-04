/*
** usage.c for myirc in /home/codeine/Projects/B4/PSU/PSU_2016_myirc/src
** 
** Made by Lucas Debouté
** Login   <lucas.deboute@epitech.eu>
** 
** Started on  Sun May 28 17:10:55 2017 Lucas Debouté
** Last update Sun Jun 11 22:48:34 2017 Lucas Debouté
*/

#include <unistd.h>

void		server_usage()
{
  write(1, "USAGE: ./server port\n", 21);
}

void	        client_usage()
{
  write(1, "USAGE: ./client adress_ip port\n", 31);
}
