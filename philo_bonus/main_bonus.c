/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:02 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/17 18:46:59 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_philo_id(t_philo *philos, pid_t pid)
{
	int i;

	i = 0;
	while (i < philos->data->num_philos)
	{
		if (pid == philos[i].pid)
			return (philos[i].id);
		i++;
	}
	return (0);
}

void	fork_philos(t_data *data)
{
	int		i;

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
	while (waitpid(-1, NULL, 0) > 0)
		;
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
