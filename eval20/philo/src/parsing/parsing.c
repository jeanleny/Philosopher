/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:32:26 by lperis            #+#    #+#             */
/*   Updated: 2025/05/16 12:20:51 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosopher.h"

int	set_value(t_data *data, char **argv, int argc)
{
	data->nb = ft_atoi(argv[1]);
	data->die_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sle_t = ft_atoi(argv[4]);
	if (argc == 6)
		data->target_meals = ft_atoi(argv[5]);
	else
		data->target_meals = -1;
	data->time = time_in_ms();
	data->id = 0;
	data->burried = 0;
	data->all_stuffed = 0;
	data->stuffed = 0;
	data->died_printed = 0;
	data->philo = malloc(sizeof(pthread_t) * data->nb);
	if (data->philo == NULL)
		return (0);
	data->mutex.fork = malloc(sizeof(pthread_mutex_t) * data->nb);
	if (data->mutex.fork == NULL)
	{
		free(data->philo);
		return (0);
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	number_parsing(int argc, char **argv)
{
	int	i;
	int	length;

	i = 1;
	while (i < argc)
	{
		if (digit(argv[i]) == 1)
		{
			printf("Wrong Arguments");
			return (0);
		}
		length = ft_zero_bin(argv[i]);
		if (overflow_check(length, argv[i]) == 1)
		{
			printf("Wrong Arguments");
			return (0);
		}
		i++;
	}
	return (1);
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
		i++;
	}
	if (number_parsing(argc, argv) == 0)
		return (0);
	if (set_value(data, argv, argc) == 0)
		return (0);
	return (1);
}
