/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:06:23 by lperis            #+#    #+#             */
/*   Updated: 2025/02/19 19:07:54 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <unistd.h>



static void	*ft_routine(void *param)
{
	t_data *data = (t_data*)param;
	static int i = 0; 
	pthread_mutex_init(&data->mutex, NULL);
	//usleep(10);
	while (1)
	{
		printf("%lo\n", data->philo[i]);
	}
	pthread_mutex_lock(&data->mutex);
	pthread_mutex_unlock(&data->mutex);
	i++;
	return (0);
}

void	init(t_data *data)
{
	data->nb = 2;
	data->fork = data->nb;
	data->eat_t = 0;
	data->die_t = 0;
	data->sle_t = 0;
	data->philo = malloc(sizeof(pthread_t) * data->nb);
}

int main(void)
{
	t_data s_data;
	int i;
	i = 0;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	init(&s_data);
	while (i < s_data.nb)
	{
		pthread_create(&s_data.philo[i], NULL, ft_routine, &s_data);
		i++;
	}
	i = 0;
	while (i < s_data.nb)
	{
		pthread_join (s_data.philo[i], NULL);
		i++;
	}
}
