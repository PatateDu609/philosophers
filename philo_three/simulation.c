/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:48:19 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 17:32:37 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		ft_wait_death(t_data *data, int quota)
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

static int		ft_monitor(t_data *data)
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

int				ft_simulate(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
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
