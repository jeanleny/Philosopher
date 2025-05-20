/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:23 by lperis            #+#    #+#             */
/*   Updated: 2025/05/19 18:23:46 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	fork_locking(t_data *data, t_philo *philo)
{
	if (!philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		action_display(data, philo, FORK, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		action_display(data, philo, FORK, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		action_display(data, philo, FORK, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		action_display(data, philo, FORK, "has taken a fork");
	}
}

void	fork_picking(t_philo *philo, t_data *data)
{
	if (data->nb == 3 && philo->id % 2 == 0)
	{
		if (time_in_ms() + data->eat_t >= time_in_ms() + data->die_t
			|| time_in_ms() - philo->last_meal_ms >= data->die_t)
		{
			ft_usleep(data->die_t, data);
		}
		else
			ft_usleep(data->eat_t, data);
	}
	else if (philo->id % 2 == 0)
		usleep(100);
	fork_locking(data, philo);
	pthread_mutex_lock(&data->mutex.burried);
	if (data->burried == 1 || data->died_printed == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&data->mutex.burried);
		return ;
	}
	pthread_mutex_unlock(&data->mutex.burried);
}

int	eat_session(t_data *data, t_philo *philo)
{
	if (death_check(data) == 1)
		return (1);
	fork_picking(philo, data);
	if (death_check(data) == 1 || meals_manager(data) == 1)
		return (1);
	if (eat_death(philo, data) == 1)
		return (1);
	if (action_display(data, philo, EAT, "is eating") == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	philo->last_meal_ms = time_in_ms();
	ft_usleep(data->eat_t, data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

static void	*ft_routine(t_data *data)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo_init(&philo, data);
	if (data->nb == 1)
	{
		one_philo(data);
		return (NULL);
	}
	while (true || data->all_stuffed == 0)
	{
		if (eat_session(data, &philo) == 1)
			break ;
		if (death_check(data) == 1)
			break ;
		if (sleep_death(&philo, data) == 1)
			break ;
		action_display(data, &philo, SLEEP, "is sleeping");
		ft_usleep(data->sle_t, data);
		if (death_check(data) == 1)
			break ;
		action_display(data, &philo, THINK, "is thinking");
		usleep(200);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	s_data;
	int		i;

	i = -1;
	if (parsing(&s_data, argc, argv) == 0)
		return (0);
	if (mutex_init(&s_data) == 0)
		return (0);
	while (++i < s_data.nb)
	{
		if (pthread_create(&s_data.philo[i], NULL,
				(void *)ft_routine, &s_data) != 0)
		{
			thread_fail(&s_data, i);
			return (0);
		}
	}
	i = 0;
	while (i < s_data.nb)
	{
		pthread_join (s_data.philo[i], NULL);
		i++;
	}
	free_data(&s_data);
}
