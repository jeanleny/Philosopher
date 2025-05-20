/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:31:35 by lperis            #+#    #+#             */
/*   Updated: 2025/05/19 17:51:37 by lperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEATH 4

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <bits/pthreadtypes.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				die_time;
	int				meals;
	long			last_meal_ms;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	id;
	pthread_mutex_t	print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	burried;
	pthread_mutex_t	meals;
}	t_mutex;

typedef struct s_data
{
	int				nb;
	int				fork;
	int				eat_t;
	int				die_t;
	int				sle_t;
	int				target_meals;
	int				stuffed;
	int				all_stuffed;
	int				id;
	int				burried;
	int				died_printed;
	long			time;
	pthread_t		*philo;
	t_mutex			mutex;
}	t_data;

int			parsing(t_data *data, int argc, char **argv);
int			ft_atoi(const char *ntpr);
long		time_in_ms(void);
void		ft_usleep(int time, t_data *data);
void		philo_init(t_philo *philo, t_data *data);
int			death_check(t_data *data);
int			mutex_init(t_data *data);
int			sleep_death(t_philo *philo, t_data *data);
int			eat_death(t_philo *philo, t_data *data);
int			action_display(t_data *data, t_philo *philo, int action,
				char *message);
int			meals_manager(t_data *data);
void		bell_ringing(t_data *data);
void		free_data(t_data *data);
void		one_philo(t_data *data);
size_t		ft_strlen(char *str);
int			overflow_check(int length, char *str);
int			digit(char *str);
void		thread_fail(t_data *data, int i);
long int	ft_atol(const char *nptr);
int			ft_zero_bin(char *str);

#endif
