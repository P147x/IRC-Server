##
## Makefile for makefile in /home/nevastuica/B4/PSU_2016_myirc
## 
## Made by Noémie
## Login   <noemie.caron@epitech.eu>
## 
## Started on  Mon May 22 12:34:04 2017 Noémie
## Last update Sun Jun 11 19:24:44 2017 Lucas Debouté
##

CC	= gcc -g
RM	= rm -f

CFLAGS	= -Wall -Wextra -I./include/

SRC	= src/server/server.c		\
	  src/server/manage_client.c	\
	  src/server/set_gfd.c		\
	  src/server/initialization.c	\
	  src/server/ringbuffer.c	\
	  src/server/send_msg.c		\
	  src/usage.c			\
	  src/scrutter.c		\
	  src/socket.c			\
	  src/get_next_line.c		\
	  src/str_to_wordtab.c		\
	  src/llist/init.c		\
	  src/llist/add.c		\
	  src/llist/free.c		\
	  src/llist/del.c		\
	  src/server/commands.c		\
	  src/server/commands/auth.c	\
	  src/server/commands/nick.c	\
	  src/server/commands/quit.c	\
	  src/server/commands/join.c	\
	  src/server/commands/part.c	\
	  src/server/commands/ping.c	\
	  src/server/commands/msg.c	\
	  src/server/commands/users.c	\
	  src/server/commands/list.c	\
	  src/server/commands/topic.c	\
	  src/server/commands/names.c	\
	  src/server/channels.c

SRC1	= src/client/client.c		\
	  src/client/initialization.c	\
	  src/client/handler.c		\
	  src/get_next_line.c		\
	  src/str_to_wordtab.c		\
	  src/usage.c			\
	  src/scrutter.c		\
	  src/socket.c

NAME	= server

NAME1	= client

OBJ	= $(SRC:.c=.o)

OBJ1	= $(SRC1:.c=.o)

all:	$(NAME) $(NAME1)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME1) $(SRC1)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ1)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME1)

re:	fclean all
