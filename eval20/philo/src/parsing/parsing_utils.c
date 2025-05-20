/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:32:43 by lperis            #+#    #+#             */
/*   Updated: 2025/05/16 12:56:59 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosopher.h"
#include "limits.h"

int	overflow_check(int length, char *str)
{
	long int	val;

	val = ft_atol(str);
	if (length > 9)
	{
		if (val > INT_MAX)
			return (1);
		if (val < INT_MIN)
			return (1);
	}
	if (length > 10)
		return (1);
	return (0);
}

int	ft_zero_bin(char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if (*str == '\0')
		return (-1);
	while (*str)
	{
		if (*str == '+' || *str == '-')
			return (0);
		str++;
		i++;
	}
	return (i);
}
