/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:36:00 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/15 20:57:47 by obouizi          ###   ########.fr       */
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

void	philo_routine(t_philo *philo)
{
	handle_edge_case(philo);
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
   