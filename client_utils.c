/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:08 by stmuller          #+#    #+#             */
/*   Updated: 2026/03/13 23:12:59 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_client;

static void	r_handler(int sig)
{
	(void)sig;
	if (sig == SIGUSR2)
		g_client = 1;
	else
		g_client = -1;
}

static int	ft_not_valid(int argnum, char **argv)
{
	int	i;

	i = 0;
	if (argnum != 3)
		return (1);
	while (argv[1][i])
	{
		if (!ft_strchr("0123456789", argv[1][i]))
			return (1);
		i++;
	}
	return (0);
}

static void	send_bit(int pid, int bit)
{
	int timeout;
	
	timeout = 0;
	if (g_client == -1)
	{
		write(1, "Server Busy!\n", 13);
		exit(1);
	}
	g_client = 0;
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (g_client == 0)
	{
		usleep(100);
		if (++timeout > 20000)
		{
			write(1, "Server timeout!\n", 16);
			exit(1);
		}
	}
}

static void	send_str(int pid, char *str)
{
	int				i;
	int				bit;
	unsigned char	c;

	i = 0;
	while (str[i])
	{
		c = (unsigned char)str[i];
		bit = 0;
		while (bit < 8)
		{
			send_bit(pid, c & 0x01);
			c = c >> 1;
			bit++;
		}
		i++;
	}
	bit = 0;
	while (bit < 8)
	{
		send_bit(pid, 0);
		bit++;
	}
}

int	main(int argnum, char **argv)
{
	struct sigaction	sa;
	int					pid;
	int					i;
	size_t				str_len;

	i = 0;
	if (ft_not_valid(argnum, argv))
		return (-1);
	str_len = ft_strlen(argv[2]);
	sa.sa_handler = r_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (-1);
	while (i < (int)(sizeof(size_t) * 8))
	{
		send_bit(pid, str_len & 0x01);
		str_len = str_len >> 1;
		i++;
	}
	send_str(pid, argv[2]);
	return (0);
}
