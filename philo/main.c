/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:24:54 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/10 21:08:30 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *p)
{
	int		i;
	long	now;
	t_philo *philos = (t_philo *) p;
	
	while (1)
	{
		i = 0;
		while (i < philos[0].data->num_philos)
		{
			if (is_stop(philos[i].data))
				return (NULL);
			pthread_mutex_lock(&philos[i].data->meal_mutex);
			now = get_time_ms(philos[i].data);
			if (now - philos[i].last_meal > philos[i].data->time_to_die)
			{
				pthread_mutex_lock(&philos[i].data->stop_mutex);
				philos[i].data->stop = 1;
				pthread_mutex_unlock(&philos[i].data->stop_mutex);
				pthread_mutex_unlock(&philos[i].data->meal_mutex);
				print_status(&philos[i], "died", 1);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].data->meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int			i;
	pthread_t	observer;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
		// usleep(100);
		i++;
	}
	pthread_create(&observer, NULL, monitor, data->philos);
	pthread_join(observer, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int main(int ac, char *av[])
{
    t_data	*data;

	data = init_data(ac, av);
	init_mutex(data);
	init_philo(data);
	data->start_time = get_time_ms(data);
	create_threads(data);
	
	clear_data(data);
    return (0);
}
