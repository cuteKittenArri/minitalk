/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:16:24 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/19 21:20:33 by stmuller         ###   ########.fr       */
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
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);


#endif