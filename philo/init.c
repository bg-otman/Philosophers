/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:23:14 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/14 13:46:26 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;
	int	is_error;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (print_error("Allocation fail\n", data), -1);
	i = 0;
	while (i < data->num_philos)
	{
		is_error = pthread_mutex_init(&data->forks[i], NULL);
		if (is_error)
			return (print_error("mutex init fail\n", data), -1);
		i++;
	}
	is_error = pthread_mutex_init(&data->stop_mutex, NULL);
	is_error = pthread_mutex_init(&data->room, NULL);
	if (is_error)
		return (print_error("mutex init fail\n", data), -1);
	is_error = pthread_mutex_init(&data->print_mutex, NULL);
	if (is_error)
		return (print_error("mutex init fail\n", data), -1);
	is_error = pthread_mutex_init(&data->meal_mutex, NULL);
	if (is_error)
		return (print_error("mutex init fail\n", data), -1);
	data->init_mutex = 1;
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (print_error("Allocation fail\n", data), -1);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_ms(data);
		if (data->philos[i].last_meal == -1)
			return (clear_data(data), -1);
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

t_data	*init_data(int ac, char *av[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		write(2, "Allocation fails!\n", 19);
		return (NULL);
	}
	memset(data, 0, sizeof(t_data));
	if (set_args(ac, av, data) == -1)
		return (NULL);
	return (data);
}

int	set_args(int ac, char *av[], t_data *data)
{
	if (ac < 5 || ac > 6)
		return (print_error("Invalid number of args\n", data), -1);
	data->num_philos = ft_atoi(av[1]);
	if (data->num_philos <= 0)
		return (print_error("At least one philo required\n", data), -1);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_die <= -1 || data->time_to_eat <= -1
		|| data->time_to_sleep <= -1)
		return (print_error("Error\n", data), -1);
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required <= 0)
			return (print_error("Need at least one meal\n", data), -1);
	}
	else
		data->meals_required = -1;
	return (0);
}

void	print_status(t_philo *philo, char *msg, int dead)
{
	long	now;
	long	elapsed;

	if (!dead && is_stop(philo->data))
		return ;
	now = get_time_ms(philo->data);
	elapsed = now - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", elapsed, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
