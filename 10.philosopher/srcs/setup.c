#include "philo.h"

int	set_input_data(int argc, char **argv, t_philo *philo)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (1);
	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		while (argv[i + 1][j])
		{
			if (!ft_isdigit(argv[i + 1][j]))
				return (1);
			j++;
		}
		if (ft_atoi2(argv[i + 1], &philo->input[i], sizeof(int)) == 0)
			return (1);
		if (philo->input[i] <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	set_person(t_table *table)
{
	t_person	*new;

	new = (t_person *)malloc(sizeof(t_person));
	if (!new)
		return (1);
	memset(new, 0, sizeof(t_person));
	if (table->first)
	{
		new->next = table->first;
		new->prev = table->last;
		table->first->prev = new;
		table->last->next = new;
	}
	else
	{
		new->next = new;
		new->prev = new;
		table->last = new;
	}
	table->first = new;
	new->id = table->length + 1;
	table->length++;
	return (0);
}

int	set_chopstick(t_table *table)
{
	t_person	*new;

	new = table->first;
	if (pthread_mutex_init(&(new->chopstick.r_lock), NULL))
		return (1);
	if (pthread_mutex_init(&(new->time_lock), NULL))
		return (1);
	if (table->length > 1)
	{
		new->chopstick.l_lock = &(new->next->chopstick.r_lock);
		new->prev->chopstick.l_lock = &(new->chopstick.r_lock);
	}
	return (0);
}

int	set_table(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->input[PHILO_NUM])
	{
		if (set_person(&philo->table))
			return (1);
		if (set_chopstick(&philo->table))
			return (1);
		philo->table.first->philo = philo;
	}
	return (0);
}

int	setup_init(int argc, char **argv, t_philo *philo)
{
	if (pthread_mutex_init(&(philo->status_lock), NULL))
		return (1);
	if (set_input_data(argc, argv, philo))
		return (1);
	if (set_table(philo))
		return (1);
	return (0);
}
