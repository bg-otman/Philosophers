/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:02 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/19 20:46:38 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	smart_sleep(t_data *data, long duration)
{
	long	start;

	start = get_time_ms(data);
	while ((get_time_ms(data) - start < duration) && !check_state(data))
		usleep(500);
}

int	get_philo_id(t_philo *philos, pid_t pid)
{
	int	i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		if (pid == philos[i].pid)
			return (philos[i].id);
		i++;
	}
	return (0);
}

void	wait_for_children(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;
	long	died_time;

	pid = 1;
	i = 0;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		died_time = get_time_ms(data) - data->start_time;
		if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_FAILURE))
		{
			sem_wait(data->sem_print);
			printf("%ld %d %s\n", died_time, get_philo_id(data->philos, pid),
				"died");
			while (i < data->num_philos)
				kill(data->philos[i++].pid, SIGKILL);
			break ;
		}
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	fork_philos(t_data *data)
{
	int	i;

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
	wait_for_children(data);
}

int	main(int ac, char *av[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	set_args(ac, av, &data);
	init_semaphores(&data);
	init_philo(&data);
	data.start_time = get_time_ms(&data);
	fork_philos(&data);
	clear_data(&data);
	return (0);
}
