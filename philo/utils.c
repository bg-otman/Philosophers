/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:17:25 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/20 13:19:14 by obouizi          ###   ########.fr       */
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
	my_deadline = philo->last_meal + philo->data->time_to_die;
	while (i < philo->data->num_philos)
	{
		other = &philo->data->philos[i];
		other_deadline = other->last_meal + philo->data->time_to_die;
		if (other_deadline < my_deadline)
			return (0);
		i++;
	}
	return (1);
}

void	safe_take_forks(t_philo *philo)
{
	while (!is_stop(philo->data))
	{
		pthread_mutex_lock(&philo->data->priority_mutex);
		if (is_my_turn(philo))
		{
			pthread_mutex_unlock(&philo->data->priority_mutex);
			take_forks(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->data->priority_mutex);
		usleep(100);
	}
}
