/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:36:00 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/16 20:23:26 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	smart_sleep(t_data *data, long duration)
{
	long	start;

	start = get_time_ms(data);
	while ((get_time_ms(data) - start < duration))
		usleep(500);
}

void	take_forks(t_philo *philo)
{
    sem_wait(philo->data->room);
    sem_wait(philo->data->forks);
    print_status(philo, "has taken a fork", 0);
    sem_wait(philo->data->forks);
    print_status(philo, "has taken a fork", 0);
    sem_post(philo->data->room);
}

void	handle_edge_case(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork", 0);
		usleep(philo->data->time_to_die * 1000);
		exit(EXIT_SUCCESS);
	}
}

void clean_exit(t_philo *philo, int status)
{
	sem_close(philo->data->forks);
	sem_close(philo->data->sem_meal);
	sem_close(philo->data->sem_print);
	sem_close(philo->data->room);
	if (philo->data->philos)
		free(philo->data->philos);
	exit(status);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	long	now;

	philo = (t_philo *) arg;
	while (1)
	{
		sem_wait(philo->data->sem_meal);
		now = get_time_ms(philo->data);
		if (now - philo->last_meal >= philo->data->time_to_die)
		{
			print_status(philo, "died", 1);
			clean_exit(philo, EXIT_FAILURE);
		}
		if (philo->meals_eaten >= philo->data->meals_required
			&& philo->data->meals_required > -1)
		{
			sem_post(philo->data->sem_meal);
			clean_exit(philo, EXIT_SUCCESS);
		}
		sem_post(philo->data->sem_meal);
		usleep(500);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

	handle_edge_case(philo);
	pthread_create(&monitor, NULL, monitor_death, philo);
	pthread_detach(monitor);
	while (1)
	{
		take_forks(philo);
		sem_wait(philo->data->sem_meal);
		philo->last_meal = get_time_ms(philo->data);
		sem_post(philo->data->sem_meal);
		print_status(philo, "is eating", 0);
		smart_sleep(philo->data, philo->data->time_to_eat);
		sem_wait(philo->data->sem_meal);
		philo->meals_eaten++;
		sem_post(philo->data->sem_meal);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_status(philo, "is sleeping", 0);
		smart_sleep(philo->data, philo->data->time_to_sleep);
		print_status(philo, "is thinking", 0);
	}
}
