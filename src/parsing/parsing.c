/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:32:26 by lperis            #+#    #+#             */
/*   Updated: 2025/02/20 20:38:51 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosopher.h"
#include <bits/pthreadtypes.h>

void	set_value(t_data *data, char **argv, int argc)
{
	data->nb = ft_atoi(argv[1]);
	data->die_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sle_t = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(pthread_t) * data->nb);
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb);
}

int	parsing(t_data *data, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong argument's amount");
		return (0);
	}
	while (i < argc)
	{
		j = ft_atoi(argv[i]);
		if (j <= 0)
		{
			printf("Wrong Arguments");
			return (0);
		}
		printf("%d\n", j);
		i++;
	}
	set_value(data, argv, argc);
	return (1);
}
