/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:48:19 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 15:54:22 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*ft_submonitor(void *arg)
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
		if (!done && philo->data->nb_eat > 0 &&
			philo->eaten >= philo->data->nb_eat)
		{
			done = 1;
			sem_post(philo->data->sem_quota);
		}
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

static int pmain(t_philo *philo)
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

static void ft_wait_death(t_data *data, int quota)
{
	pid_t	pid;
	int		i;

	if (!quota)
		pid = waitpid(-1, NULL, 0);
	i = 0;
	while (i < data->nb_philos)
	{
		if (quota || data->philosophers[i] != pid)
			kill(data->philosophers[i], SIGTERM);
		i++;
	}
}

static int ft_monitor(t_data *data)
{
	int		i;

	if (data->nb_eat < 0)
		return (0);
	i = 0;
	while (i < data->nb_philos)
	{
		sem_wait(data->sem_quota);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		sem_post(data->sem_quota);
		i++;
	}
	return (1);
}

int	ft_simulate(t_data *data, t_philo *philo)
{
	int		i = 0;

	data->start = ft_timestamp(NULL);
	while (i < data->nb_philos)
	{
		data->philosophers[i] = fork();
		if (!data->philosophers[i])
			exit(pmain(philo + i));
		usleep(100);
		i++;
	}
	if (data->nb_eat > 0)
		ft_monitor(data);
	ft_wait_death(data, data->nb_eat >= 0);
	return (1);
}
