#include "philo.h"

void	thread_init_behavior(t_philo *philo)
{
	int			i;
	t_person	*curr;

	i = -1;
	curr = philo->table.first;
	while (++i < philo->table.length)
	{
		pthread_create(&curr->pthread, NULL, thread_behavior, (void *)curr);
		pthread_detach(curr->pthread);
		curr = curr->next;
	}
}

void	thread_init_monitor(t_philo *philo)
{
	int			i;
	t_person	*curr;

	i = -1;
	curr = philo->table.first;
	while (++i < philo->table.length)
	{
		pthread_create(&curr->monitor, NULL, thread_monitor, (void *)curr);
		curr = curr->next;
	}
}

int	thread_init(t_philo *philo)
{
	int			i;
	t_person	*curr;


	pthread_mutex_lock(&philo->status_lock);

	gettime(&philo->time_init);
	thread_init_behavior(philo);
	thread_init_monitor(philo);

	pthread_mutex_unlock(&philo->status_lock);

	i = -1;
	curr = philo->table.first;
	while (++i < philo->table.length)
	{
		pthread_join(curr->monitor, NULL);
		curr = curr->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(philo));
	if (setup_init(argc, argv, &philo))
		return (1);
	thread_init(&philo);
	return (0);
}
