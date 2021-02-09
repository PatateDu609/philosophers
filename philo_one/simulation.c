/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:00:29 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 17:11:31 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			*ft_philo(void *arg)
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

static int		ft_check_philos(t_data *data, t_philo *philo, int *quota)
{
	int		i;
	int		end;
	long	ts;

	i = 0;
	end = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(data->m_access + i);
		if (data->nb_eat > 0 && philo[i].eaten >= data->nb_eat)
			quota[i] = 1;
		ts = ft_timestamp(data);
		if (!philo[i].eating
			&& philo[i].last_eat + data->time_die < ts)
		{
			print_message(DIED, philo + i);
			end = 1;
		}
		pthread_mutex_unlock(data->m_access + i++);
		if (end)
			break ;
		usleep(100);
	}
	return (end);
}

static void		ft_monitor(t_data *data, t_philo *philo)
{
	int		end;
	int		*quota;
	int		i;

	end = 0;
	quota = malloc(sizeof(int) * data->nb_philos);
	memset(quota, 0, sizeof(int) * data->nb_philos);
	while (!end)
	{
		if (ft_check_philos(data, philo, quota))
			break ;
		i = 0;
		while (i < data->nb_philos && quota[i])
			if (++i == data->nb_philos)
				end = 1;
	}
	data->finish = 1;
	free(quota);
}

static void		ft_wait_death(t_data *data, t_philo *philo)
{
	int		count;
	int		i;

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

int				ft_simulate(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	data->start = ft_timestamp(NULL);
	while (i < data->nb_philos)
	{
		if (pthread_create(data->philosophers + i, NULL, ft_philo, philo + i))
			return (0);
		if (pthread_detach(data->philosophers[i]))
			return (0);
		usleep(10);
		i++;
	}
	ft_monitor(data, philo);
	ft_wait_death(data, philo);
	return (1);
}
