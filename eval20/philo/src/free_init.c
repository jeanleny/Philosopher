/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:03:20 by lperis            #+#    #+#             */
/*   Updated: 2025/03/12 12:36:33 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	philo_init(t_philo *philo, t_data *data)
{
	philo->meals = 0;
	philo->last_meal_ms = time_in_ms();
	philo->die_time = data->die_t;
	pthread_mutex_lock(&data->mutex.id);
	philo->id = data->id;
	philo->left_fork = &data->mutex.fork[philo->id];
	philo->right_fork = &data->mutex.fork[(philo->id + 1) % data->nb];
	data->id++;
	pthread_mutex_unlock(&data->mutex.id);
}

int	mutex_init(t_data *data)
{
	int	i;
	int	exit;

	exit = 0;
	i = 0;
	if (pthread_mutex_init(&data->mutex.print, NULL) != 0)
		exit = 1;
	if (pthread_mutex_init(&data->mutex.burried, NULL) != 0)
		exit = 1;
	if (pthread_mutex_init(&data->mutex.meals, NULL) != 0)
		exit = 1;
	if (pthread_mutex_init(&data->mutex.id, NULL) != 0)
		exit = 1;
	if (exit == 1)
	{
		free_data(data);
		return (0);
	}
	while (i < data->nb)
	{
		if (pthread_mutex_init(&data->mutex.fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	free_data(t_data *data)
{
	free(data->philo);
	free(data->mutex.fork);
}
