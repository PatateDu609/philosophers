/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:36:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/25 14:45:26 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_take_fork(t_philo *philo)
{
	int		tmp;
	int		first;
	int		second;

	first = philo->nb;
	second = (philo->nb + 1) % philo->data->nb_philos;
	if (philo->nb % 2)
	{
		tmp = first;
		first = second;
		second = tmp;
	}
	pthread_mutex_lock(philo->data->m_forks + first);
	print_message(TAKEN_FORK, philo);
	pthread_mutex_lock(philo->data->m_forks + second);
	print_message(TAKEN_FORK, philo);
}

static void	ft_leave_fork(t_philo *philo)
{
	int		first;
	int		second;

	first = philo->nb;
	second = (philo->nb + 1) % philo->data->nb_philos;
	pthread_mutex_unlock(philo->data->m_forks + first);
	pthread_mutex_unlock(philo->data->m_forks + second);
}

static void	ft_eat(t_philo *philo)
{
	long last_eat;

	last_eat = print_message(EATING, philo);
	pthread_mutex_lock(philo->data->m_access + philo->nb);
	philo->eating = 1;
	philo->eaten++;
	philo->last_eat = last_eat;
	pthread_mutex_unlock(philo->data->m_access + philo->nb);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_lock(philo->data->m_access + philo->nb);
	philo->eating = 0;
	pthread_mutex_unlock(philo->data->m_access + philo->nb);
}

static int ft_finish(t_philo *philo)
{
	pthread_mutex_lock(philo->data->m_access + philo->nb);
	philo->running = 0;
	pthread_mutex_unlock(philo->data->m_access + philo->nb);
	return (0);
}

int	ft_action(t_philo *philo, t_events event)
{
	if (philo->data->finish && event != EAT && event != LEAVE_FORK)
		return (ft_finish(philo));
	else if (philo->data->finish && event == EAT)
		return (0);
	if (event == TAKE_FORK)
	{
		ft_take_fork(philo);
		return (1);
	}
	else if (event == LEAVE_FORK)
		ft_leave_fork(philo);
	else if (event == THINK)
		print_message(THINKING, philo);
	else if (event == SLEEP)
	{
		print_message(SLEEPING, philo);
		usleep(philo->data->time_sleep * 1000);
	}
	else if (event == EAT)
		ft_eat(philo);
	return (1);
}
