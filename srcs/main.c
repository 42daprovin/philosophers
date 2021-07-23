/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:59:13 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/24 01:11:11 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	g_data;

void	*philosophers(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->p_id % 2 == 0)
		usleep(500);
	while (g_data.death == 0)
	{
		if (g_data.death)
			break;
		pthread_mutex_lock(&g_data.fork[(philo->p_id % g_data.philos) - 1]);
		printf("%ld %d has taken a fork\n", conv_time(&g_data.tp, &g_data.tzp) - g_data.time, philo->p_id);
		pthread_mutex_lock(&g_data.fork[philo->p_id % g_data.philos]);
		printf("%ld %d has taken a fork\n", conv_time(&g_data.tp, &g_data.tzp) - g_data.time, philo->p_id);
		if (g_data.death)
		{
			pthread_mutex_unlock(&g_data.fork[(philo->p_id % g_data.philos) - 1]);
			pthread_mutex_unlock(&g_data.fork[philo->p_id % g_data.philos]);
			break;
		}
		philo->last_eat = conv_time(&g_data.tp, &g_data.tzp);
		printf("%ld %d is eating\n", philo->last_eat - g_data.time, philo->p_id);
		ft_usleep(g_data.t_to_eat, philo->last_eat, &g_data.tp, &g_data.tzp);
		pthread_mutex_unlock(&g_data.fork[(philo->p_id % g_data.philos) - 1]);
		pthread_mutex_unlock(&g_data.fork[philo->p_id % g_data.philos]);
		philo->last_sleep = conv_time(&g_data.tp, &g_data.tzp);
		if (g_data.death)
			break;
		printf("%ld %d is sleeping\n", philo->last_sleep - g_data.time, philo->p_id);
		ft_usleep(g_data.t_to_sleep, philo->last_sleep, &g_data.tp, &g_data.tzp);
		if (g_data.death)
			break;
		printf("%ld %d is thinking\n", conv_time(&g_data.tp, &g_data.tzp) - g_data.time, philo->p_id);
	}
	return (NULL);
	/* pthread_exit(NULL); */
}

void	init_data(char **av, int ac)
{
	int	i;

	g_data.philos = atoi(av[1]);		//write ft_atoi
	g_data.t_to_die = atoi(av[2]);
	g_data.t_to_eat = atoi(av[3]);
	g_data.t_to_sleep = atoi(av[4]);
	g_data.death = 0;
	if (ac == 6)
		g_data.n_eat = atoi(av[5]);
	else
		g_data.n_eat = -1;
	g_data.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_data.philos);
	if (!g_data.fork)
		exit (1);
	i = 0;
	while (i < g_data.philos)
	{
		pthread_mutex_init(&((g_data.fork)[i]), NULL);
		i++;
	}
}

void	init_philo(void)
{
	t_philo	philo[g_data.philos];
	int	i;
	long last_eat;
	
	i = 0;
	while (i < g_data.philos)
	{
		philo[i].p_id = i + 1;
		philo[i].last_eat = 0;
		philo[i].t_eat = 0;
		pthread_create(&(philo[i].t_id), NULL, philosophers, (void *)&philo[i]);
		i++;
	}
	while (g_data.death == 0)
	{
	 	i = 0;
		while (i < g_data.philos)
		{
			/* printf("t_id -----------> %d\n", philo[i].p_id); */
			long jaume;
			last_eat = philo[i].last_eat;
			if ((jaume = conv_time(&g_data.tp, &g_data.tzp)) - last_eat >= g_data.t_to_die && last_eat != 0)
			{
				printf("ts = %ld, last_eat = %ld, to_die = %ld\n", jaume, last_eat, g_data.t_to_die);
				g_data.death = 1;
				printf("%ld %d died\n", conv_time(&g_data.tp, &g_data.tzp) - g_data.time, i + 1);
				/* i = 0; */
				/* while (i < g_data.philos) */
				/* { */
				/* 	pthread_detach(philo[i].t_id); */
				/* 	i++; */
				/* } */
				break ;
			}
			i++;
		}	
	}
	i = 0;
	while (i < g_data.philos)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;

	init_data(av, ac);
	settimeofday(&g_data.tp, &g_data.tzp);
	g_data.time = conv_time(&g_data.tp, &g_data.tzp);
	init_philo();
	free(g_data.fork);
	return (0);
}
