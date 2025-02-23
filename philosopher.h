#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct	s_philo
{
	int		id;
	int		die_time;
	long	last_meal_ms;
}	t_philo;

typedef struct	s_mutex
{
	pthread_mutex_t	id;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
}	t_mutex;

typedef struct s_data
{
	int nb;
	int fork;
	int	eat_t;
	int	die_t;
	int	sle_t;
	int	meals;
	int	id;
	long			time;
	pthread_t		*philo;
	t_mutex			mutex;
} t_data;

int		parsing(t_data *data, int argc, char **argv);
int		ft_atoi(const char *ntpr);
long	time_in_ms(void);

#endif
