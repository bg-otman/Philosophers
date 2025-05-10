/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:20:34 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/10 21:09:22 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
	pthread_t		thread;
	long			last_meal;
	int				id;
	int				meals_eaten;
} t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_philos;
	int				meals_required;
	int				stop;
} t_data;

// helpers
long	ft_atoi(const char *str);
void	print_error(char *msg, t_data *data);
size_t	ft_strlen(const char *s);
long	get_time_ms(t_data *data);
void	clear_data(t_data *data);
// init
void	set_args(int ac, char *av[], t_data *data);
t_data	*init_data(int ac, char *av[]);
void	init_mutex(t_data *data);
void	init_philo(t_data *data);
// philo
void	*philo_routine(void *p);
void	print_status(t_philo *philo, char *msg, int dead);
void	smart_sleep(t_data *data, long duration);
int		is_stop(t_data *data);

#endif
