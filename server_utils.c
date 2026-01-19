/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:20 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/19 22:15:50 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static void	ft_receiver(int signal)
{
	static int	str_len = 0;

	if (!str_len)
		ft_receive_len();
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