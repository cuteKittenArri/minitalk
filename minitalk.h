/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:16:24 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/20 00:12:06 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(int c, const char *s);
int		ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
void	ft_putnbr_fd(long n, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_power_to(int nb, int power);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr_fd(char *s, int fd);

#endif