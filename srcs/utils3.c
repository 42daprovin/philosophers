
#include "philo.h"

int	check_0(char c)
{
	if (c == '0')
	{
		write(2, "Error: at least 1 philosopher needed\n", 37);
		return (1);
	}
	return (0);
}

void	death(void)
{
	pthread_mutex_lock(&g_data.prot_eat_die);
	g_data.death = 1;
	pthread_mutex_unlock(&g_data.prot_eat_die);
}
