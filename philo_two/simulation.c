/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:48:19 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 17:22:10 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
			sem_wait(philo->data->sem_access[philo->nb]);
			philo->running = 0;
			sem_post(philo->data->sem_access[philo->nb]);
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

	end = 0;
	i = 0;
	while (i < data->nb_philos)
	{
		sem_wait(data->sem_access[i]);
		if (data->nb_eat > 0 && philo[i].eaten >= data->nb_eat)
			quota[i] = 1;
		ts = ft_timestamp(data);
		if (!philo[i].eating
			&& philo[i].last_eat + data->time_die < ts)
		{
			print_message(DIED, philo + i);
			end = 1;
		}
		sem_post(data->sem_access[i++]);
		if (end)
			break ;
		usleep(100);
	}
	return (end);
}

static void		ft_monitor(t_data *data, t_philo *philo)
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
	int count;
	int i;

	count = 0;
	while (count != data->nb_philos)
	{
		i = 0;
		count = 0;
		while (i < data->nb_philos)
		{
			sem_wait(data->sem_access[i]);
			count += !philo[i].running;
			sem_post(data->sem_access[i++]);
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
		usleep(100);
		i++;
	}
	ft_monitor(data, philo);
	ft_wait_death(data, philo);
	return (1);
}
