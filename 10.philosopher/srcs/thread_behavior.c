#include "philo.h"

void	take_sleep(t_person *curr)
{
	print_curr(curr, "is sleeping");
	ft_sleep(curr->philo->input[PHILO_SLEEP]);
	print_curr(curr, "is thinking");
}

void	meal_lock(t_person *curr,
			pthread_mutex_t *first,
			pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
	gettime(&curr->time_start);
	print_curr(curr, "has taken a fork");
	print_curr(curr, "is eating");
	ft_sleep(curr->philo->input[PHILO_EAT]);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	take_meal(t_person *curr)
{
	if (!curr->chopstick.l_lock)
		ft_sleep(curr->philo->input[PHILO_DEATH] + 100);
	if (curr->id % 2 == 0)
		meal_lock(curr, curr->chopstick.l_lock, &curr->chopstick.r_lock);
	else
	{
		usleep(10);
		meal_lock(curr, &curr->chopstick.r_lock, curr->chopstick.l_lock);
	}
}

void	*thread_behavior(void *p)
{
	t_person	*curr;

	curr = (t_person *)p;
	while (!curr->philo->status)
	{
		if (curr->philo->input[PHILO_OPT] && \
				curr->eat > curr->philo->input[PHILO_OPT])
			return (0);
		take_meal(curr);
		take_sleep(curr);
		curr->eat++;
	}
	return (0);
}
