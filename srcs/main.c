/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:59:13 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/26 18:25:29 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	g_data;

void	*philothread(void *v_philo)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)v_philo;
	id = philo->p_id;
	if (philo->p_id % 2 == 0)
		usleep(800);
	while (g_data.death == 0)
	{
		if (g_data.death)
			break ;
		philo_forks(id);
		if (g_data.death)
		{
			pthread_mutex_unlock(&g_data.fork[(id - 1) % g_data.philos]);
			pthread_mutex_unlock(&g_data.fork[id % g_data.philos]);
			break ;
		}
		philo_eat_sleep(philo, id);
		if (g_data.death)
			break ;
		printf("%ld %d is thinking\n",
			conv_time(&g_data.tp, &g_data.tzp) - g_data.time, id);
	}
	return (NULL);
}

void	init_data(char **av, int ac)
{
	int	i;

	g_data.philos = ft_atoi(av[1]);
	g_data.t_to_die = ft_atoi(av[2]);
	g_data.t_to_eat = ft_atoi(av[3]);
	g_data.t_to_sleep = ft_atoi(av[4]);
	g_data.death = 0;
	g_data.t_eat = -1;
	if (ac == 6)
		g_data.n_eat = ft_atoi(av[5]);
	else
		g_data.n_eat = -1;
	g_data.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* g_data.philos);
	if (!g_data.fork)
		exit (1);
	i = 0;
	while (i < g_data.philos)
	{
		pthread_mutex_init(&((g_data.fork)[i]), NULL);
		i++;
	}
}

void	philosophers(void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * g_data.philos);
	if (!philo)
		exit(1);
	i = 0;
	while (i < g_data.philos)
	{
		init_philo(&philo[i], i);
		i++;
	}
	while (g_data.death == 0)
		check_death_eat(philo);
	join_threads(philo);
	free(philo);
}

int	main(int ac, char **av)
{
	if (check_data(ac, av))
		return (1);
	init_data(av, ac);
	settimeofday(&g_data.tp, &g_data.tzp);
	g_data.time = conv_time(&g_data.tp, &g_data.tzp);
	philosophers();
	free(g_data.fork);
	return (0);
}
