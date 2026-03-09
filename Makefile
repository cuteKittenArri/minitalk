# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 17:59:21 by stmuller          #+#    #+#              #
#    Updated: 2026/03/09 19:12:02 by stmuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME := client
SERVER_NAME := server
CC := cc
CFLAGS := -Wall -Werror -Wextra
CLIENT_SRC := client_utils.c libft_utils_dos.c libft_utils.c
SERVER_SRC := server_utils.c libft_utils_dos.c libft_utils.c
CLIENT_OBJ := $(CLIENT_SRC:.c=.o)
SERVER_OBJ := $(SERVER_SRC:.c=.o)
HEAD := minitalk.h

all: client server

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT_NAME)

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER_NAME)

clean:
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	rm -rf $(CLIENT_NAME) $(SERVER_NAME)

re: clean all

.PHONY: all clean fclean re