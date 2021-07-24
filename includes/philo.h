/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:50:31 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/24 22:03:20 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_philo
{
	pthread_t	t_id;
	long		last_eat;
	long		last_sleep;
	int			p_id;
	int			t_eat;
}				t_philo;

typedef struct	s_data
{
	struct timeval	tp;
	struct timezone	tzp;
	long			time;
	pthread_mutex_t	*fork;
	int				death;
	long			t_to_eat;
	long			t_to_sleep;
	long			t_to_die;
	int				n_eat;
	int				t_eat;
	int				philos;
}				t_data;

t_data	g_data;

void	ft_usleep(long slp, long time, struct timeval *tp, struct timezone *tzp);

long	conv_time(struct timeval *tp, struct timezone *tzp);

int		times_eat(int p_t_eat, int i);

int		check_data(int ac, char **av);

#endif
