/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:02 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/15 20:54:06 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	stop_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (!data->philos)
		return ;
	while(i < data->num_philos)
	{
		kill(data->philos[i].pid, SIGTERM);
		i++;
	}
}

int	check_death(t_philo *philos, int i, int ate_enough)
{
	long	now;

	sem_wait(philos[i].data->sem_meal);
	now = get_time_ms(philos[i].data);
	if (now - philos[i].last_meal > philos[i].data->time_to_die)
	{
		stop_simulation(philos[i].data);
		sem_post(philos[i].data->sem_meal);
		print_status(&philos[i], "died", 1);
		exit(EXIT_SUCCESS);
	}
	if ((philos[i].meals_eaten >= philos->data->meals_required)
		&& philos->data->meals_required > -1)
		ate_enough++;
	sem_post(philos[i].data->sem_meal);
	return (ate_enough);
}

void	monitor(t_philo *philos)
{
	int		i;
	int		ate_enough;

	while (1)
	{
		i = 0;
		ate_enough = 0;
		while (i < philos->data->num_philos)
		{
			ate_enough = check_death(philos, i, ate_enough);
			i++;
		}
		if (ate_enough == philos->data->num_philos)
		{
			stop_simulation(philos->data);
			exit(EXIT_SUCCESS);
		}
		usleep(500);
	}
}

void	fork_philos(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			print_error("fork failed\n", data);
		else if (data->philos[i].pid == 0)
			philo_routine(&data->philos[i]);
		i++;
	}
	pid = fork();
	if (pid == -1)
		print_error("fork failed\n", data);
	else if (pid == 0)
		monitor(data->philos);
	else
	{
		while(waitpid(-1, NULL, 0) > 0);
	}
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = init_data(ac, av);
	init_semaphores(data);
	init_philo(data);
	data->start_time = get_time_ms(data);
	fork_philos(data);
	clear_data(data);
	return (0);
}
