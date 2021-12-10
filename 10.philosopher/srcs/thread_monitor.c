#include "philo.h"

void	*thread_monitor(void *p)
{
	t_person	*curr;
	long		now;
	long		lap;

	curr = (t_person *)p;
	while (!curr->philo->status)
	{
		if (curr->philo->input[PHILO_OPT] && \
				curr->eat > curr->philo->input[PHILO_OPT])
			return (0);
		gettime(&now);
		lap = now - curr->time_start;
		if (lap > curr->philo->input[PHILO_DEATH])
		{
			print_curr(curr, RED"died"RESET);
			pthread_mutex_lock(&curr->philo->status_lock);
			curr->philo->status |= 1;
			pthread_mutex_unlock(&curr->philo->status_lock);
		}

		if (lap / 2 > curr->philo->input[PHILO_DEATH])
			usleep(lap / 2);
		else
			usleep(100);
	}
	return (0);
}
