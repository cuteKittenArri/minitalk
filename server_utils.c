/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:20 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/20 00:13:52 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_receive_len(int *str_len_recived, int signal, char **str, int *bit_at)
{
	static int	str_len = 0;
	
	if (signal == SIGUSR1)
		str_len = ft_power_to(2, *bit_at);
	if (*bit_at == 31)
	{
		*str_len_recived = 1;
		*str = ft_calloc(str_len + 1, sizeof(char));
		*bit_at = 0;
		str_len = 0;
		return ;
	}
	(*bit_at)++;
}
static void	ft_free(int *i, char **str, int *str_len_recived)
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
		if (signal == SIGUSR1)
			curr_char += ft_power_to(2, bit_at);
		if (bit_at == 7)
		{
			str[i++] = curr_char;
			bit_at = 0;
			if (curr_char == 0)
				return (ft_free(&i, &str, &str_len_recived));
			curr_char = 0;
			return ;
		}
		bit_at++;
	}
}

int	main(void)
{
	ft_putnbr_fd((int)getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, ft_receiver);
	signal(SIGUSR2, ft_receiver);
	while (1)
		usleep(100);
}