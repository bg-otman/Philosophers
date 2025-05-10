/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:45:57 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/10 16:41:12 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    ft_atoi(const char *str)
{
	long	nb;
	int     i;
	int     sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (str && ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' ')))
		i++;
	if (str && str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str && str[i] == '+')
		i++;
	while (str && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

size_t  ft_strlen(const char *s)
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
		print_error("gettimeofday() error\n", data);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	clear_data(t_data *data)
{
	if (data->forks)
	{
		while (data->num_philos--)
			pthread_mutex_destroy(&data->forks[data->num_philos]);
		free(data->forks);
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
