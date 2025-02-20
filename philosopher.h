#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
	int nb;
	int fork;
	int	eat_t;
	int	die_t;
	int	sle_t;
	int	meals;
	long			time;
	pthread_t		*philo;
	pthread_mutex_t	*mutex;
} t_data;

int	parsing(t_data *data, int argc, char **argv);
int		ft_atoi(const char *ntpr);

#endif
