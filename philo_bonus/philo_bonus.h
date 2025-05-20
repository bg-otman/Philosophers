/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:07 by obouizi           #+#    #+#             */
/*   Updated: 2025/05/20 13:56:04 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define SEM_NAME "/philo_sem"
# define SEM_STOP "/sem_stop"
# define SEM_PRINT "/sem_print"
# define SEM_MEAL "/sem_meal"
# define SEM_ROOM "/sem_room"

typedef struct s_philo
{
	struct s_data	*data;
	long			last_meal;
	int				id;
	pid_t			pid;
	int				meals_eaten;
}					t_philo;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*sem_stop;
	sem_t			*sem_print;
	sem_t			*sem_meal;
	sem_t			*room;
	t_philo			*philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_philos;
	int				meals_required;
	int				stop;
}					t_data;
// helpers
long				ft_atoi(const char *str);
long				get_time_ms(t_data *data);
void				print_error(char *msg, t_data *data);
void				clear_data(t_data *data);
size_t				ft_strlen(const char *s);
// init
void				set_args(int ac, char *av[], t_data *data);
void				init_semaphores(t_data *data);
void				init_philo(t_data *data);
// philo
void				philo_routine(t_philo *philo);
void				smart_sleep(t_data *data, long duration);
void				stop_simulation(t_data *data);
void				set_stop(t_data *data);
void				*monitor(void *arg);
int					check_state(t_data *data);
// utils
void				clean_exit(t_philo *philo, int status);
void				print_status(t_philo *philo, char *msg);
pthread_t			call_monitor(t_philo *philo, void *monitor(void *));

#endif