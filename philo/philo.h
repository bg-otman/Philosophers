/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:20:34 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/14 13:43:47 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
	pthread_t		thread;
	long			last_meal;
	int				id;
	int				meals_eaten;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	room;
	t_philo			*philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_philos;
	int				meals_required;
	int				stop;
	int				init_mutex;// to check mutex is intialised before destroy it
}					t_data;

// helpers
long				ft_atoi(const char *str);
void				print_error(char *msg, t_data *data);
size_t				ft_strlen(const char *s);
long				get_time_ms(t_data *data);
void				clear_data(t_data *data);
// init
int					set_args(int ac, char *av[], t_data *data);
t_data				*init_data(int ac, char *av[]);
int					init_mutex(t_data *data);
int					init_philo(t_data *data);
void				print_status(t_philo *philo, char *msg, int dead);
// philo
void				*philo_routine(void *p);
void				smart_sleep(t_data *data, long duration);
void				stop_simulation(t_data *data);
int					is_stop(t_data *data);

#endif
