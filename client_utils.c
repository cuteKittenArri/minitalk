/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stmuller <stmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:50:08 by stmuller          #+#    #+#             */
/*   Updated: 2026/01/17 18:55:36 by stmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	
	
}