/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:23 by lperis            #+#    #+#             */
/*   Updated: 2025/02/23 16:56:09 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

long	time_in_ms(void)
{
	long			tms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	tms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (tms);
}

void	death(t_philo *philo)
{
	while(true)
	{
		if (philo->last_meal_ms != 0)
		{
			usleep(philo->die_time);
			if (time_in_ms() < philo->last_meal_ms)
				exit(1);
			philo->last_meal_ms = 0;
		}
	}
}

void	philo_init(t_philo *philo, t_data *data)
{
	pthread_t	death_checker;
	philo->die_time = data->die_t;
	pthread_create(&death_checker, NULL, (void *)death, &philo);
	pthread_mutex_init(&data->mutex.id, NULL);
	pthread_mutex_lock(&data->mutex.id);
	philo->id = data->id;
	data->id++;
	pthread_mutex_unlock(&data->mutex.id);
	pthread_mutex_init(&data->mutex.fork[philo->id], NULL);
	pthread_mutex_init(&data->mutex.fork[(philo->id + 1) % data->nb], NULL);
}

void	fork_picking(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->mutex.fork[philo->id]);
		printf("%ld %d has taken a fork\n",
			time_in_ms() - data->time, philo->id + 1);
		pthread_mutex_lock(&data->mutex.fork[(philo->id + 1) % data->nb]);
		printf("%ld %d has taken a fork\n",
			time_in_ms() - data->time, philo->id + 1);
	}
	else
	{
		pthread_mutex_lock(&data->mutex.fork[(philo->id + 1) % data->nb]);
		printf("%ld %d has taken a fork\n",
			time_in_ms() - data->time, philo->id + 1);
		pthread_mutex_lock(&data->mutex.fork[philo->id]);
		printf("%ld %d has taken a fork\n",
			time_in_ms() - data->time, philo->id + 1);
	}
}

static void	*ft_routine(t_data *data)
{
	t_philo	philo;

	philo_init(&philo, data);
	while (true)
	{
		fork_picking(&philo, data);
		pthread_mutex_unlock(&data->mutex.fork[(philo.id + 1) % data->nb]);
		pthread_mutex_unlock(&data->mutex.fork[philo.id]);
		printf("%ld %d is eating\n", time_in_ms() - data->time, philo.id + 1);
		usleep(data->eat_t);
		philo.last_meal_ms = time_in_ms();
		printf("%ld %d is sleeping\n", time_in_ms() - data->time, philo.id + 1);
		usleep(data->sle_t);
		printf("%ld %d is thinking\n", time_in_ms() - data->time, philo.id + 1);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	s_data;
	int		i;

	i = 0;
	if (parsing(&s_data, argc, argv) == 0)
		return (0);
	while (i < s_data.nb)
	{
		pthread_create(&s_data.philo[i], NULL, (void *)ft_routine, &s_data);
		i++;
	}
	i = 0;
	while (i < s_data.nb)
	{
		pthread_join (s_data.philo[i], NULL);
		i++;
	}
}
