/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:07 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/15 16:11:20 by obouizi          ###   ########.fr       */
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
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>

# define SEM_NAME "/philo_sem"

typedef struct s_philo
{
	sem_t			*l_fork;
	sem_t			*r_fork;
	struct s_data	*data;
	pthread_t		thread;
	long			last_meal;
	int				id;
	int				meals_eaten;
}					t_philo;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			stop_mutex;
	sem_t			print_mutex;
	sem_t			meal_mutex;
	t_philo			*philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_philos;
	int				meals_required;
	int				stop;
	int				init_mutex;
}					t_data;

// helpers
long				ft_atoi(const char *str);
void				print_error(char *msg, t_data *data);
size_t				ft_strlen(const char *s);
long				get_time_ms(t_data *data);
void				clear_data(t_data *data);
// init
void				set_args(int ac, char *av[], t_data *data);
t_data				*init_data(int ac, char *av[]);
void				init_mutex(t_data *data);
void				init_philo(t_data *data);
void				print_status(t_philo *philo, char *msg, int dead);
// philo
void				*philo_routine(void *p);
void				smart_sleep(t_data *data, long duration);
void				stop_simulation(t_data *data);
int					is_stop(t_data *data);

#endif