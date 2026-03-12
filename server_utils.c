/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arri <arri@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:20 by stmuller          #+#    #+#             */
/*   Updated: 2026/03/12 21:27:35 by arri             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static struct s_state	g_server;

static void	handler(int signal, siginfo_t *info, void *ctx)
{
	(void)ctx;
	if (g_server.client_pid != 0 && g_server.client_pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	g_server.signal = signal;
	g_server.client_pid = info->si_pid;
	g_server.new_signal = 1;
}

static void	recived_len(void)
{
	if (g_server.signal == SIGUSR1)
		g_server.str_len |= ((size_t) 1 << g_server.bit_i);
	g_server.bit_i++;
	if (g_server.bit_i == (int)(sizeof(size_t) * 8))
	{
		g_server.str = ft_calloc(g_server.str_len + 2, sizeof(char));
		if (!g_server.str)
		{
			write(1, "Memory allocation failed!\n", 26);
			exit(-1);
		}
		g_server.bit_i = 0;
		g_server.len_recived = 1;
	}
	kill(g_server.client_pid, SIGUSR2);
}

static void	recived_char(void)
{
	if (g_server.signal == SIGUSR1)
		g_server.curr_char |= (1 << g_server.bit_i);
	g_server.bit_i++;
	if (g_server.bit_i == 8)
	{
		g_server.str[g_server.str_i++] = (char) g_server.curr_char;
		g_server.bit_i = 0;
		if (g_server.curr_char == 0)
		{
			ft_putstr_fd(g_server.str, 1);
			ft_putchar_fd('\n', 1);
			free(g_server.str);
			g_server.str = 0;
			g_server.str_len = 0;
			g_server.str_i = 0;
			g_server.len_recived = 0;
			kill(g_server.client_pid, SIGUSR2);
			g_server.client_pid = 0;
			return ;
		}
		g_server.curr_char = 0;
	}
	kill(g_server.client_pid, SIGUSR2);
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
		if (g_server.new_signal)
		{
			g_server.new_signal = 0;
			if (!g_server.len_recived)
				recived_len();
			else
				recived_char();
		}
		usleep(100);
	}
}
