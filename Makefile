# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 17:59:21 by stmuller          #+#    #+#              #
#    Updated: 2026/03/09 18:25:36 by stmuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT := client
SERVER := server
CC := cc
CFLAGS := -Wall -Werror -Wextra
CLIENT_SRC := client_utils.c libft_utils_dos.c libft_utils.c
SERVER_SRC := server_utils.c libft_utils_dos.c libft_utils.c
HEAD := minitalk.h

all: $(CLIENT) $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) $(CLIENT_SRC)

$(SERVER):
	$(CC) $(CFLAGS) $(SERVER_SRC)

clean:
	rm -rf $(CLIENT) $(SERVER)

re: clean all

.PHONY: all clean re