#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/26 19:04:30 by ppellegr          #+#    #+#              #
#    Updated: 2015/03/26 19:04:31 by ppellegr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME0=serveur
NAME1=client
VERSION=0.0.1
CFLAGS=-Wall -Werror -Wextra -g
CC = clang
INCLUDES=-I libft/includes
LIB=libft/libft.a
SRC0=server.c server_loop.c clean_fd.c client_io.c client_io2.c check_fd.c srv_accept.c \
cmd_serv.c cmd_serv2.c ret_string_split.c
SRC1=client.c client_loop.c cmd_client.c client_loop2.c
OBJ0=$(SRC0:.c=.o)
OBJ1=$(SRC1:.c=.o)

all: $(NAME0) $(NAME1) finish

build:
	@($(MAKE) -C ./libft)

$(NAME0): 
	$(CC) $(CFLAGS) -c $(SRC0) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME0) $(OBJ0) $(LIB)

$(NAME1):	
	$(CC) $(CFLAGS) -c $(SRC1) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1) $(LIB)

clean:
	@(rm -rf $(OBJ0))
	@(rm -rf $(OBJ1))

fclean: clean
	@(rm -rf $(NAME0))
	@(rm -rf $(NAME1))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all clean fclean re v