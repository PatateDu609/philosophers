/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:36:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 20:49:26 by gboucett         ###   ########.fr       */
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

void	ft_action(t_philo *philo, t_events event)
{
	if (event == TAKE_FORK)
	{
		ft_take_fork(philo);
		return ;
	}
	if (event == LEAVE_FORK)
		ft_leave_fork(philo);
	else if (event == SLEEP)
	{
		print_message(SLEEPING, philo);
		usleep(philo->data->time_sleep);
	}
	else if (event == EAT)
	{
		print_message(EATING, philo);
		usleep(philo->data->time_eat);
	}
}
