#include "philo.h"

void	gettime(long *ret)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	*ret = (timeval.tv_sec * 1000) + timeval.tv_usec / 1000;
}

void	ft_sleep(long sleep)
{
	long	start;
	long	now;

	gettime(&start);
	gettime(&now);
	while (now - start <= sleep)
		gettime(&now);
}

void	print_curr(t_person *curr, char *str)
{
	long	now;

	gettime(&now);
	pthread_mutex_lock(&curr->philo->status_lock);
	if (curr->philo->status)
	{
		pthread_mutex_unlock(&curr->philo->status_lock);
		return ;
	}
	printf(YELLOW"%6lu"RESET"ms  ", now - curr->philo->time_init);
	printf("%3d" " %-18s" GREEN" (%d)\n"RESET, curr->id, str, curr->eat);
	pthread_mutex_unlock(&curr->philo->status_lock);
}
