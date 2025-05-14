/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:26:02 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/14 12:57:47 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	stop_simulation(t_data *data)
{
	// pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	// pthread_mutex_unlock(&data->stop_mutex);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = init_data(ac, av);
	
	init_philo(data);
	data->start_time = get_time_ms(data);
	create_threads(data);
	clear_data(data);
	return (0);
}
