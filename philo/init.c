/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:23:14 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/13 14:35:11 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		print_error("Allocation fail\n", data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		print_error("Allocation fail\n", data);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_ms(data);
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
}

t_data	*init_data(int ac, char *av[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		write(2, "Allocation fails!\n", 19);
		exit(EXIT_FAILURE);
	}
	memset(data, 0, sizeof(t_data));
	set_args(ac, av, data);
	return (data);
}

void	set_args(int ac, char *av[], t_data *data)
{
	if (ac < 5 || ac > 6)
		print_error("Invalid number of args\n", data);
	data->num_philos = ft_atoi(av[1]);
	if (data->num_philos <= 0)
		print_error("At least one philo required\n", data);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required <= 0)
			print_error("Need at least one meal\n", data);
	}
	else
		data->meals_required = -1;
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
