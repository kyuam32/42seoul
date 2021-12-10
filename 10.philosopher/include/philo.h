#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define PHILO_NUM 0
# define PHILO_DEATH 1
# define PHILO_EAT 2
# define PHILO_SLEEP 3
# define PHILO_OPT 4

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

typedef struct s_chopstick
{
	pthread_mutex_t	r_lock;
	pthread_mutex_t	*l_lock;
}				t_chopstick;

typedef struct s_person
{
	struct s_philo		*philo;
	int					id;
	int					eat;
	long				time_start;
	pthread_mutex_t		time_lock;
	t_chopstick			chopstick;
	pthread_t			pthread;
	pthread_t			monitor;
	struct s_person		*next;
	struct s_person		*prev;
}				t_person;

typedef struct s_table
{
	t_person	*first;
	t_person	*last;
	int			length;
}				t_table;

typedef struct s_philo
{
	long			input[5];
	t_table			table;
	int				status;
	pthread_mutex_t	status_lock;
	long			time_init;
}				t_philo;

int		setup_init(int argc, char **argv, t_philo *philo);
int		thread_init(t_philo *philo);
void	*thread_behavior(void *p);
void	*thread_monitor(void *p);
void	print_curr(t_person *curr, char *str);
void	ft_sleep(long sleep);
void	gettime(long *ret);
int		ft_atoi2(const char *str, void *ret, int sizeoftype);
int		ft_isdigit(int c);

#endif
