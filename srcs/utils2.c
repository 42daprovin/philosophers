/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 21:13:27 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/25 22:31:44 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_forks(int id)
{
	pthread_mutex_lock(&g_data.fork[(id - 1) % g_data.philos]);
	if (!g_data.death)
		printf("%ld %d has taken a fork\n",
			conv_time(&g_data.tp, &g_data.tzp) - g_data.time, id);
	pthread_mutex_lock(&g_data.fork[id % g_data.philos]);
	if (!g_data.death)
		printf("%ld %d has taken a fork\n",
			conv_time(&g_data.tp, &g_data.tzp) - g_data.time, id);
}

void	philo_eat_sleep(t_philo *philo, int id)
{
	philo->last_eat = conv_time(&g_data.tp, &g_data.tzp);
	printf("%ld %d is eating\n", philo->last_eat - g_data.time, id);
	philo->t_eat = philo->t_eat + 1;
	ft_usleep(g_data.t_to_eat, philo->last_eat, &g_data.tp, &g_data.tzp);
	pthread_mutex_unlock(&g_data.fork[(id - 1) % g_data.philos]);
	pthread_mutex_unlock(&g_data.fork[id % g_data.philos]);
	philo->last_sleep = conv_time(&g_data.tp, &g_data.tzp);
	if (g_data.death)
		return ;
	printf("%ld %d is sleeping\n", philo->last_sleep - g_data.time, id);
	ft_usleep(g_data.t_to_sleep, philo->last_sleep, &g_data.tp, &g_data.tzp);
}

void	init_philo(t_philo *philo, int i)
{
	philo->p_id = i + 1;
	philo->last_eat = 0;
	philo->t_eat = 0;
	pthread_create(&(philo->t_id), NULL, philothread, (void *)philo);
	i++;
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < g_data.philos)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
}

void	check_death_eat(t_philo *philo)
{
	int		i;
	long	last_eat;

	i = 0;
	g_data.t_eat = -1;
	while (i < g_data.philos)
	{
		if (times_eat(philo[i].t_eat, i))
		{
			g_data.death = 1;
			break ;
		}
		last_eat = philo[i].last_eat;
		if (conv_time(&g_data.tp, &g_data.tzp) - last_eat
			>= g_data.t_to_die && last_eat != 0)
		{
			g_data.death = 1;
			printf("%ld %d died\n",
				conv_time(&g_data.tp, &g_data.tzp) - g_data.time, i + 1);
			break ;
		}
		i++;
	}
}
