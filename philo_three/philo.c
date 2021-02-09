/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:32:24 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 17:32:51 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		ft_check_quota(t_philo *philo, int done)
{
	if (!done && philo->data->nb_eat > 0 &&
		philo->eaten >= philo->data->nb_eat)
	{
		done = 1;
		sem_post(philo->data->sem_quota);
	}
	return (done);
}

static void		*ft_submonitor(void *arg)
{
	t_philo		*philo;
	long		ts;
	int			done;

	philo = (t_philo *)arg;
	sem_wait(philo->data->sem_quota);
	done = 0;
	while (1)
	{
		sem_wait(philo->sem_access);
		ts = ft_timestamp(philo->data);
		done = ft_check_quota(philo, done);
		if (!philo->eating && philo->last_eat + philo->data->time_die < ts)
		{
			sem_post(philo->data->sem_quota);
			print_message(DIED, philo);
			sem_post(philo->sem_access);
			exit(0);
		}
		sem_post(philo->sem_access);
		usleep(100);
	}
	return (NULL);
}

int				pmain(t_philo *philo)
{
	pthread_create(&philo->monitor, NULL, ft_submonitor, philo);
	philo->running = 1;
	while (1)
	{
		if (!ft_action(philo, TAKE_FORK))
			return (0);
		if (!ft_action(philo, EAT))
		{
			ft_action(philo, LEAVE_FORK);
			sem_wait(philo->sem_access);
			philo->running = 0;
			sem_post(philo->sem_access);
			return (0);
		}
		ft_action(philo, LEAVE_FORK);
		if (!ft_action(philo, SLEEP))
			return (0);
		if (!ft_action(philo, THINK))
			return (0);
	}
	return (0);
}
