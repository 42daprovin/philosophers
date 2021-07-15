/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:59:13 by daprovin          #+#    #+#             */
/*   Updated: 2021/07/15 23:07:36 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	struct timeval	tp;
	struct timezone	tzp;
	long			time;

	settimeofday(&tp, &tzp);	
	gettimeofday(&tp, &tzp);
	
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;	
	printf("%ld\n", time);
	usleep(1000000);
	gettimeofday(&tp, &tzp);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;	
	printf("%ld\n", time);
	return (0);
}
