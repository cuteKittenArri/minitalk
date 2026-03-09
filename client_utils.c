/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arri <arri@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:08 by stmuller          #+#    #+#             */
/*   Updated: 2026/03/09 14:41:16 by arri             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	server_r;

static void	r_handler(int sig)
{
	(void)sig;
	server_r = 1;
}
static int	ft_not_valid(int argnum, char **argv){
	int	i;
	
	i = 0;
	if (argnum != 3)
		return (1);
	while (argv[1][i])
	{
		if (!ft_strchr(argv[1][i], "0123456789"))
			return (1);
		i++;
	}
	return (0);
}

static void send_bit(int pid, int bit)
{
	server_r = 0;
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (!server_r)
		usleep(100);
}
static void	send_len(int pid, size_t str_len)
{
	int	i;

	i = 0;
	while (i < (sizeof(size_t) * 8))
	{
		send_bit(pid, str_len & 0x01);
		str_len = str_len >> 1;
		i++;
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

int	main(int argnum, char **argv){
	struct sigaction	sa;
	int					pid;

	if (ft_not_valid(argnum, argv))
		return (-1);
	sa.sa_handler = r_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (-1);

	send_len(pid, ft_strlen(argv[2]));
	send_str(pid, argv[2]);
	return (0);
}
