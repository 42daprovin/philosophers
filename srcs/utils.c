/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:37:31 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/25 22:29:28 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	conv_time(struct timeval *tp, struct timezone *tzp)
{
	long int	time;

	gettimeofday(tp, tzp);
	time = tp->tv_sec * 1000 + tp->tv_usec / 1000;
	return (time);
}

void	ft_usleep(long slp, long time, struct timeval *tp, struct timezone *tzp)
{
	while (conv_time(tp, tzp) - time < slp)
	{
		usleep(500);
	}
}

int	times_eat(int p_t_eat, int i)
{
	if (g_data.n_eat < 0)
		return (0);
	if (p_t_eat >= g_data.n_eat && g_data.t_eat != 0)
		g_data.t_eat = 1;
	else
		g_data.t_eat = 0;
	if (g_data.t_eat == 1 && i == (g_data.philos - 1))
		return (1);
	else
		return (0);
}

int	is_not_a_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

int	check_data(int ac, char **av)
{
	int	i;

	if (ac < 5)
	{
		write(2, "Error: too few arguents\n", 24);
		return (1);
	}
	if (ac > 6)
	{
		write(2, "Error: too many arguents\n", 25);
		return (1);
	}
	i = 1;
	while (av[i])
	{
		if (is_not_a_number(av[i]))
		{
			write(2, "Error: arguments can be only positive numbers\n", 46);
			return (1);
		}
		i++;
	}
	return (0);
}
