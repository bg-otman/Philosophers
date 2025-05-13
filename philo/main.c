/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:24:54 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/13 18:56:24 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

int	check_death(t_philo *philos, int i, int ate_enough)
{
	long	now;

	pthread_mutex_lock(&philos[i].data->meal_mutex);
	now = get_time_ms(philos[i].data);
	if (now - philos[i].last_meal > philos[i].data->time_to_die)
	{
		stop_simulation(philos[i].data);
		pthread_mutex_unlock(&philos[i].data->meal_mutex);
		print_status(&philos[i], "died", 1);
		return (-2);
	}
	if ((philos[i].meals_eaten >= philos->data->meals_required)
		&& philos->data->meals_required > -1)
		ate_enough++;
	pthread_mutex_unlock(&philos[i].data->meal_mutex);
	return (ate_enough);
}

void	*monitor(void *p)
{
	int		i;
	int		ate_enough;
	t_philo	*philos;

	philos = (t_philo *)p;
	while (1)
	{
		i = 0;
		ate_enough = 0;
		while (i < philos->data->num_philos)
		{
			if (is_stop(philos[i].data))
				return (NULL);
			ate_enough = check_death(philos, i, ate_enough);
			if (ate_enough == -2)
				return (NULL);
			i++;
		}
		if (ate_enough == philos->data->num_philos)
			stop_simulation(philos->data);
		usleep(500);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	pthread_t	observer;

	int (i), (is_error);
	i = 0;
	while (i < data->num_philos)
	{
		is_error = pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]);
		if (is_error)
			return (print_error("Failed to create Thread\n", data));
		i++;
	}
	is_error = pthread_create(&observer, NULL, monitor, data->philos);
	if (is_error)
		return (print_error("Failed to create Thread\n", data));
	is_error = pthread_join(observer, NULL);
	if (is_error)
		return (print_error("Failed to join Thread\n", data));
	i = 0;
	while (i < data->num_philos)
	{
		is_error = pthread_join(data->philos[i++].thread, NULL);
		if (is_error)
			return (print_error("Failed to join Thread\n", data));
	}
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = init_data(ac, av);
	if (!data)
		return (1);
	if (init_mutex(data) == -1)
		return (2);
	if (init_philo(data) == -1)
		return (3);
	data->start_time = get_time_ms(data);
	if (data->start_time == -1)
		return (5);
	create_threads(data);
	clear_data(data);
	return (0);
}
