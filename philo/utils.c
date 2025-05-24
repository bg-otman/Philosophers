/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:17:25 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/24 15:31:09 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_my_turn(t_philo *philo)
{
	int		i;
	long	my_deadline;
	long	other_deadline;
	t_philo	*other;

	i = 0;
	pthread_mutex_lock(&philo->data->meal_mutex);
	my_deadline = philo->last_meal + philo->data->time_to_die;
	while (i < philo->data->num_philos)
	{
		other = &philo->data->philos[i];
		other_deadline = other->last_meal + philo->data->time_to_die;
		if (other_deadline < my_deadline)
		{
			pthread_mutex_unlock(&philo->data->meal_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (1);
}

void	safe_eat(t_philo *philo)
{
	while (!is_stop(philo->data))
	{
		pthread_mutex_lock(&philo->data->priority_mutex);
		if (is_my_turn(philo))
		{
			pthread_mutex_unlock(&philo->data->priority_mutex);
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
			return ;
		}
		pthread_mutex_unlock(&philo->data->priority_mutex);
		usleep(100);
	}
}
