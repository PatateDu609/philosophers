/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:59:53 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 17:19:03 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

typedef enum e_events
{
	DIED = -1,
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FORK,
}	t_events;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		nb;
	t_data	*data;
}	t_philo;

struct s_data
{
	long	start;

	int		nb_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_eat;
};

void	print_message(t_events event, t_philo *philo);
long	ft_timestamp(t_data *data);
int		ft_atoi(char *str);
int		ft_init(t_data *data, int ac, char **av);
int		usage(void);

#endif
