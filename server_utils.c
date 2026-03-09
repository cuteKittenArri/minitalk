/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arri <arri@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:20 by stmuller          #+#    #+#             */
/*   Updated: 2026/03/09 14:45:34 by arri             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static struct state server_state;

static void	handler(int signal, siginfo_t *info, void *ctx)
{
	(void)ctx;
	server_state.signal = signal;
	server_state.client_pid = info->si_pid;
	server_state.new_signal = 1;
}

static void recived_len(void)
{
	if (server_state.signal == SIGUSR1)
		server_state.str_len |= ((size_t) 1 << server_state.bit_i);
	server_state.bit_i++;
	if (server_state.bit_i == (int)(sizeof(size_t) * 8))
	{
		server_state.str = ft_calloc(server_state.str_len + 2, sizeof(char));
		server_state.bit_i = 0;
		server_state.len_recived = 1;
	}
	kill(server_state.client_pid, SIGUSR2);
}

static void	recived_char(void)
{
	if (server_state.signal == SIGUSR1)
		server_state.curr_char |= (1 << server_state.bit_i);
	server_state.bit_i++;
	if (server_state.bit_i == 8)
	{
		server_state.str[server_state.str_i++] = (char) server_state.curr_char;
		server_state.bit_i = 0;
		if (server_state.curr_char == 0)
		{
			ft_putstr_fd(server_state.str, 1);
			ft_putchar_fd('\n', 1);
			free(server_state.str);
			server_state.str = 0;
			server_state.str_len = 0;
			server_state.str_i = 0;
			server_state.len_recived = 0;
		}
		server_state.curr_char = 0;
	}
	kill(server_state.client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putnbr_fd((long)getpid(), 1);
	ft_putchar_fd('\n', 1);
	
	while (1)
	{
		if (server_state.new_signal)
		{
			server_state.new_signal = 0;
			if (!server_state.len_recived)
				recived_len();
			else
				recived_char();
		}
		usleep(100);
	}
}