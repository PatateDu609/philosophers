/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:59:53 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 20:48:49 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_events
{
	DIED = -1,
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FORK,
	TAKE_FORK,
	EAT,
	SLEEP,
	LEAVE_FORK,
}	t_events;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		nb;
	long	last_eat;
	t_data	*data;
}	t_philo;

struct s_data
{
	long				start;

	int					nb_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;

	pthread_mutex_t		*m_forks;
	pthread_mutex_t		m_write;
	pthread_mutex_t		m_run;
	pthread_t			*philosophers;
};

void	print_message(t_events event, t_philo *philo);
long	ft_timestamp(t_data *data);
int		ft_atoi(char *str);
int		usage(void);

int		ft_free_all(t_data *data, int status);

void	ft_action(t_philo *philo, t_events event);

int		ft_init_mutex(t_data *data);
t_philo	*ft_init_philos(t_data *data);
int		ft_init(t_data *data, int ac, char **av);

#endif
