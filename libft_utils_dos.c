/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_dos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:41:10 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/20 01:42:11 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*r;

	r = s;
	i = 0;
	while (i < n)
	{
		*r = 0;
		r++;
		i++;
	}
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	max;

	max = 0;
	max--;
	if (nmemb == 0 || size == 0)
	{
		array = (malloc(1));
		ft_bzero(array, 1);
		return (array);
	}
	if (size >= max / nmemb)
		return (0);
	array = malloc(size * nmemb);
	if (!array)
		return (0);
	ft_bzero(array, nmemb * size);
	return (array);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	minus;

	result = 0;
	minus = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == ' ')
	{
		nptr++;
	}
	if (*nptr == '-')
	{
		minus = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 +(*nptr -48);
		nptr++;
	}
	return (result * minus);
}

size_t	ft_power_to(size_t nb, size_t power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
		return (nb * ft_power_to(nb, power - 1));
}
