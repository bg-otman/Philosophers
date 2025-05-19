/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:34:16 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/19 19:57:45 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_ROOM);
	data->forks = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, data->num_philos);
	data->sem_stop = sem_open(SEM_STOP, O_CREAT | O_EXCL, 0644, 1);
	data->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	data->sem_meal = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 0644, 1);
	data->room = sem_open(SEM_ROOM, O_CREAT | O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->sem_print == SEM_FAILED
		|| data->sem_meal == SEM_FAILED || data->room == SEM_FAILED
		|| data->sem_stop == SEM_FAILED)
		print_error("open semaphores fails\n", data);
}

void	init_philo(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		print_error("Allocation fail\n", data);
	memset(data->philos, 0, sizeof(t_philo) * data->num_philos);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_ms(data);
		data->philos[i].data = data;
		i++;
	}
}

void	set_args(int ac, char *av[], t_data *data)
{
	if (ac < 5 || ac > 6)
		print_error("Invalid number of args\n", data);
	data->num_philos = ft_atoi(av[1]);
	if (data->num_philos <= 0 || data->num_philos >= 100000)
		print_error("Error in philos num\n", data);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_die <= -1 || data->time_to_eat <= -1
		|| data->time_to_sleep <= -1)
		print_error("Error\n", data);
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required <= 0)
			print_error("Error in meal required\n", data);
	}
	else
		data->meals_required = -1;
}
