/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:23 by lperis            #+#    #+#             */
/*   Updated: 2025/02/20 20:47:49 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"
#include <pthread.h>
#include <unistd.h>

static void	*ft_routine(t_data *data)
{
	int				i;

	while (1)
	{
		i = 0;
		while (data->philo[i])
		{
			pthread_mutex_lock(&data->mutex[i]);
			pthread_mutex_lock(&data->mutex[(i + 1) % data->nb]);
			printf("%lo %d has taken a fork1\n", data->time, i + 1);
			printf("%lo %d has taken a fork2\n", data->time, i + 1);
			pthread_mutex_unlock(&data->mutex[i]);
			pthread_mutex_unlock(&data->mutex[(i + 1) % data->nb]);
			printf("%d is eating\n", i + 1);
			usleep(data->eat_t * 1000);
			printf("%d is sleeping\n", i + 1);
			usleep(data->sle_t * 1000);
			printf("%d is thinking\n", i + 1);
			i++;
		}
	}
	return (0);
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
