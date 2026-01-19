/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:08 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/20 00:18:14 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static void	send_len(int pid, int str_len)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (str_len & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		str_len = str_len >> 1;
		i++;
		usleep(100);
	}
	
}
static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c = c >> 1;
		usleep(100);
		i++;
	}
}

int	main(int argnum, char **argv){
	int		pid;
	int		i;
	char	*str;
	int		str_len;

	if (ft_not_valid(argnum, argv))
		return (-1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (-1);
	str = argv[2];
	str_len = ft_strlen(str);
	send_len(pid, str_len);
	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, str[i]);
}
