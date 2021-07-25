/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:44:04 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/25 19:34:42 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	n;

	i = 0;
	sig = 1;
	n = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1 * sig;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i++] - 48);
		if (n < 0 && sig == -1)
			return (0);
		if (n < 0 && sig == 1)
			return (-1);
	}
	return (sig * n);
}
