/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:00:29 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/08 23:03:28 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->running = 1;
	while (1)
	{
		if (!ft_action(philo, TAKE_FORK))
			return (NULL);
		if (!ft_action(philo, EAT))
		{
			ft_action(philo, LEAVE_FORK);
			pthread_mutex_lock(philo->data->m_access + philo->nb);
			philo->running = 0;
			pthread_mutex_unlock(philo->data->m_access + philo->nb);
			return (NULL);
		}
		ft_action(philo, LEAVE_FORK);
		if (!ft_action(philo, SLEEP))
			return (NULL);
		if (!ft_action(philo, THINK))
			return (NULL);
	}
	return (NULL);
}

static void ft_monitor(t_data *data, t_philo *philo)
{
	int	i;
	int	end;
	int *quota;

	end = 0;
	quota = malloc(sizeof(int) * data->nb_philos);
	memset(quota, 0, sizeof(int) * data->nb_philos);
	while (!end)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(data->m_access + i);
			if (data->nb_eat > 0 && philo[i].eaten >= data->nb_eat)
				quota[i] = 1;
			long ts = ft_timestamp(data);
			if (!philo[i].eating
				&& philo[i].last_eat + data->time_die < ts)
			{
				print_message(DIED, philo + i);
				end = 1;
			}
			dprintf(threads, "i = %d, eating ? %d, end = %d, limit = %ld, current = %ld\n", i, philo[i].eating, end, philo[i].last_eat + data->time_die, ts);
			pthread_mutex_unlock(data->m_access + i++);
			if (end)
				break ;
			usleep(100);
		}
		if (end)
			break ;
		i = 0;
		while (i < data->nb_philos && quota[i])
			if (++i == data->nb_philos)
				end = 1;
	}
	data->finish = 1;
	free(quota);
}

static void ft_wait_death(t_data *data, t_philo* philo)
{
	int count;
	int i;

	count = 0;
	while (count != data->nb_philos)
	{
		i = 0;
		count = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(data->m_access + i);
			count += !philo[i].running;
			pthread_mutex_unlock(data->m_access + i++);
			usleep(100);
		}
	}
}

int	ft_simulate(t_data *data, t_philo *philo)
{
	int i = 0;

	data->start = ft_timestamp(NULL);
	while (i < data->nb_philos)
	{
		if (pthread_create(data->philosophers + i, NULL, ft_philo, philo + i))
			return (0);
		if (pthread_detach(data->philosophers[i]))
			return (0);
		usleep(100);
		i++;
	}
	ft_monitor(data, philo);
	ft_wait_death(data, philo);
	return (1);
}
