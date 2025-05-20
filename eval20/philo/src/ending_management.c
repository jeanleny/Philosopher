/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:04:22 by lperis            #+#    #+#             */
/*   Updated: 2025/05/19 17:51:48 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	sleep_death(t_philo *philo, t_data *data)
{
	if (time_in_ms() + data->sle_t > time_in_ms() + data->die_t
		|| time_in_ms() - philo->last_meal_ms + data->sle_t > data->die_t)
	{
		action_display(data, philo, SLEEP, "is sleeping");
		ft_usleep(data->die_t, data);
		pthread_mutex_lock(&data->mutex.burried);
		if (data->burried == 1)
		{
			pthread_mutex_unlock(&data->mutex.burried);
			return (1);
		}
		data->burried = 1;
		pthread_mutex_unlock(&data->mutex.burried);
		action_display(data, philo, DEATH, "died");
		return (1);
	}
	return (0);
}

void	one_philo(t_data *data)
{
	printf("%ld 1 has taken a fork\n", time_in_ms() - data->time);
	ft_usleep(data->die_t, data);
	printf("%ld 1 died\n", time_in_ms() - data->time);
	pthread_mutex_lock(&data->mutex.burried);
	data->burried = 1;
	pthread_mutex_unlock(&data->mutex.burried);
	return ;
}

int	eat_death(t_philo *philo, t_data *data)
{
	if (time_in_ms() + data->eat_t > time_in_ms() + data->die_t
		|| time_in_ms() - philo->last_meal_ms > data->die_t)
	{
		action_display(data, philo, EAT, "is eating");
		ft_usleep(data->die_t, data);
		pthread_mutex_lock(&data->mutex.burried);
		if (data->burried == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(&data->mutex.burried);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex.burried);
		pthread_mutex_lock(&data->mutex.burried);
		data->burried = 1;
		pthread_mutex_unlock(&data->mutex.burried);
		action_display(data, philo, DEATH, "died");
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

int	meals_manager(t_data *data)
{
	pthread_mutex_lock(&data->mutex.print);
	if (data->died_printed == 1)
	{
		pthread_mutex_unlock(&data->mutex.print);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex.print);
	return (0);
}

int	death_check(t_data *data)
{
	pthread_mutex_lock(&data->mutex.burried);
	if (data->burried == 1)
	{
		pthread_mutex_unlock(&data->mutex.burried);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex.burried);
	return (0);
}
