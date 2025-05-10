/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:29:02 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/10 21:08:34 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

void	smart_sleep(t_data *data, long duration)
{
	long	start;
	
	start = get_time_ms(data);
	while ((get_time_ms(data) - start < duration) && !is_stop(data))
		usleep(500);
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

void	*philo_routine(void *p)
{
	t_philo *philo = (t_philo *) p;

	while (!is_stop(philo->data))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, "has taken a fork", 0);
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, "has taken a fork", 0);
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, "has taken a fork", 0);
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, "has taken a fork", 0);
		}
		print_status(philo, "is eating", 0);
		smart_sleep(philo->data, philo->data->time_to_eat);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		print_status(philo, "is sleeping", 0);
		smart_sleep(philo->data, philo->data->time_to_sleep);
		print_status(philo, "is thinking", 0);
	}
	return (NULL);
}
