/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/15 12:07:08 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi(const char *str)
{
	long		nb;
	int			i;

	nb = 0;
	i = 0;
	while (str && ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' ')))
		i++;
	if (str && str[i] == '+')
		i++;
	if (!str[i])
		return (print_error("Error\n", NULL), -1);
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (print_error("Error\n", NULL), -1);
		if (nb > (LONG_MAX - (str[i] - '0')) / 10)
			return (print_error("Error\n", NULL), -1);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

long	get_time_ms(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (print_error("gettimeofday() error\n", data), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (data->forks)
	{
		while (i < data->num_philos && data->init_mutex)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->init_mutex)
	{
		pthread_mutex_destroy(&data->stop_mutex);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		pthread_mutex_destroy(&data->room);
	}
	if (data->philos)
		free(data->philos);
	free(data);
}

void	print_error(char *msg, t_data *data)
{
	write(2, msg, ft_strlen(msg));
	clear_data(data);
	exit(EXIT_FAILURE);
}
