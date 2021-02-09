/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:59:53 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 04:05:38 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# define _GNU_SOURCE

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>

typedef enum e_events
{
	DIED = -1,
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FORK,
	THINK,
	TAKE_FORK,
	EAT,
	SLEEP,
	LEAVE_FORK,
}	t_events;

typedef struct s_data	t_data;

typedef struct s_data
{
	long				start;
	int					finish;

	int					nb_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;

	pid_t				*philosophers;
	sem_t				*sem_quota;
	sem_t				*sem_forks;
}	t_data;

typedef struct s_philo
{
	int			nb;
	int			eaten;
	int			eating;
	long		last_eat;
	int			running;
	t_data		*data;

	pthread_t	monitor;
	sem_t		*sem_access;
}	t_philo;

long	print_message(t_events event, t_philo *philo);

long	ft_timestamp(t_data *data);
int		ft_atoi(char *str);
int		usage(void);
char	*get_access(int i);

int		ft_free_all(t_data *data, int status);

int		ft_init_semaphore(t_data *data);
int		ft_init(t_data **data, int ac, char **av);
int		ft_init_philos(t_data *data, t_philo **philos);

int		ft_action(t_philo *philo, t_events event);
int		ft_simulate(t_data *data, t_philo *philo);

extern int threads;
extern int threads2;

#endif
