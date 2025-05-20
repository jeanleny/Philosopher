/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:57:58 by lperis            #+#    #+#             */
/*   Updated: 2025/05/19 17:45:17 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	ft_usleep(int time, t_data *data)
{
	long	end;

	end = time_in_ms() + time;
	while (end > time_in_ms())
	{
		pthread_mutex_lock(&data->mutex.burried);
		if (data->burried == 1)
		{
			pthread_mutex_unlock(&data->mutex.burried);
			break ;
		}
		else
			pthread_mutex_unlock(&data->mutex.burried);
		usleep(100);
	}
	return ;
}

long	time_in_ms(void)
{
	long			tms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	tms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (tms);
}

void	death_n_meals(t_data *data, t_philo *philo, int action, char *message)
{
	if (action == DEATH && data->died_printed == 0)
	{
		data->died_printed = 1;
		printf("%ld %d died\n", time_in_ms() - data->time, philo->id + 1);
	}
	else if (action == EAT && data->died_printed == 0)
	{
		if (data->target_meals > 0)
		{
			philo->meals++;
			if (philo->meals == data->target_meals)
				data->stuffed++;
			if (data->stuffed == data->nb)
				data->died_printed = 1;
		}
		printf("%ld %d %s\n", time_in_ms() - data->time, philo->id + 1,
			message);
	}
}

int	action_display(t_data *data, t_philo *philo, int action, char *message)
{
	pthread_mutex_lock(&data->mutex.print);
	if (data->died_printed == 1)
	{
		pthread_mutex_unlock(&data->mutex.print);
		return (1);
	}
	if (action == DEATH || action == EAT)
		death_n_meals(data, philo, action, message);
	else
		printf("%ld %d %s\n", time_in_ms() - data->time, philo->id + 1,
			message);
	pthread_mutex_unlock(&data->mutex.print);
	return (0);
}

void	thread_fail(t_data *data, int i)
{
	data->burried = 1;
	i--;
	while (i > 0)
	{
		pthread_join(data->philo[i], NULL);
		i--;
	}
	pthread_join(data->philo[0], NULL);
	free_data(data);
	return ;
}
