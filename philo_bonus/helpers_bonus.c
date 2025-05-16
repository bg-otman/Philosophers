/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:15 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/16 20:24:08 by obouizi          ###   ########.fr       */
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
		return (-1);
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		if (nb > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
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
	sem_close(data->forks);
	sem_unlink(SEM_NAME);
	sem_close(data->sem_meal);
	sem_unlink(SEM_PRINT);
	sem_close(data->sem_meal);
	sem_unlink(SEM_MEAL);
	sem_close(data->room);
	sem_unlink(SEM_ROOM);
	if (data->philos)
		free(data->philos);
}

void	print_error(char *msg, t_data *data)
{
	write(2, msg, ft_strlen(msg));
	clear_data(data);
	exit(EXIT_FAILURE);
}
