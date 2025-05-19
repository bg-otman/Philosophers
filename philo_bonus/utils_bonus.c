/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:56:54 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/19 19:59:38 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_exit(t_philo *philo, int status)
{
	sem_close(philo->data->forks);
	sem_close(philo->data->sem_meal);
	sem_close(philo->data->sem_stop);
	sem_close(philo->data->sem_print);
	sem_close(philo->data->room);
	if (philo->data->philos)
		free(philo->data->philos);
	exit(status);
}

pthread_t	call_monitor(t_philo *philo, void *monitor(void *))
{
	pthread_t	thread;

	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		exit(EXIT_SUCCESS);
	}
	if (pthread_create(&thread, NULL, monitor, philo))
		print_error("thread creation fails\n", philo->data);
	return (thread);
}

void	print_status(t_philo *philo, char *msg)
{
	long	now;
	long	elapsed;

	if (check_state(philo->data))
		return ;
	now = get_time_ms(philo->data);
	elapsed = now - philo->data->start_time;
	sem_wait(philo->data->sem_print);
	if (!check_state(philo->data))
		printf("%ld %d %s\n", elapsed, philo->id, msg);
	sem_post(philo->data->sem_print);
}
