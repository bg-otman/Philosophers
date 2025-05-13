/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:29:02 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/13 18:50:01 by obouizi          ###   ########.fr       */
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
	if (start == -1)
		return ;
	while ((get_time_ms(data) - start < duration) && !is_stop(data))
		usleep(500);
}

void	take_forks(t_philo *philo)
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
		usleep(300);
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork", 0);
	}
}

int	handle_edge_case(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork", 0);
		usleep(philo->data->time_to_die * 1000);
		return (1);
	}
	return (0);
}

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (handle_edge_case(philo))
		return (NULL);
	while (!is_stop(philo->data))
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->last_meal = get_time_ms(philo->data);
		pthread_mutex_unlock(&philo->data->meal_mutex);
		print_status(philo, "is eating", 0);
		smart_sleep(philo->data, philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		print_status(philo, "is sleeping", 0);
		smart_sleep(philo->data, philo->data->time_to_sleep);
		print_status(philo, "is thinking", 0);
	}
	return (NULL);
}
