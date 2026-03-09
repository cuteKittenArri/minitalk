/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:20 by stmuller          #+#    #+#             */
/*   Updated: 2026/03/09 01:36:45 by stmuller         ###   ########.fr       */
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
	if (server_state.signal = SIGUSR1)
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















static void	ft_receive_len(int *str_len_recived, int signal, char **str, int *bit_at)
{
	static size_t	str_len = 0;
	
	if (signal == SIGUSR1)
		server_state.str_len  = ft_power_to(2, server_state.bit_i);
	if (*bit_at == (sizeof(size_t) * 8) - 1)
	{
		*str_len_recived = 1;
		printf("%zu", str_len);
		*str = ft_calloc(str_len + 2, sizeof(char));
		if (!(*str))
		{
			write(1, "EROOOR, ka was da ned geht", 27);
			return ;
		}
		*bit_at = 0;
		str_len = 0;
		return ;
	}
	(*bit_at)++;
}
static void	ft_print(int *i, char **str, int *str_len_recived)
{
	*str_len_recived = 0;
	*i = 0;
	if (str)
	{
		ft_putstr_fd(*str, 1);
		ft_putchar_fd('\n', 1);
		free(*str);
		str = 0;
	}
}

static void	ft_receiver(int signal)
{
	static int	str_len_recived = 0;
	static char	*str = 0;
	static int	i = 0;
	static int	bit_at = 0;
	static int	curr_char = 0;

	if (!str_len_recived)
		ft_receive_len(&str_len_recived, signal, &str, &bit_at);
	else
	{
		if (signal == 1)
			curr_char += ft_power_to(2, bit_at);
		if (bit_at == 7)
		{
			str[i++] = curr_char;
			bit_at = 0;
			if (curr_char == 0)
				return (ft_print(&i, &str, &str_len_recived));
			curr_char = 0;
			return ;
		}
		bit_at++;
	}
}

static void	ft_signalhandler(int signal)
{
	if (SIGUSR1 == signal)
		recived_bit = 1;
	else if (SIGUSR2 == signal)
		recived_bit = 2;
}

int	main(void)
{
	ft_putnbr_fd((int)getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, ft_signalhandler);
	signal(SIGUSR2, ft_signalhandler);
	while (1)
	{
		if (recived_bit == 1)
		{
			ft_receiver(1);
			recived_bit = 0;
		}
		else if (recived_bit == 2)
		{
			ft_receiver(2);
			recived_bit = 0;
		}
		usleep(10);
	}
}
