/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 19:37:31 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/23 19:37:34 by daprovin         ###   ########.fr       */
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
