/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:36:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 03:40:28 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_take_fork(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	print_message(TAKEN_FORK, philo);
	sem_wait(philo->data->sem_forks);
	print_message(TAKEN_FORK, philo);
}

static void	ft_leave_fork(t_philo *philo)
{
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
}

static void	ft_eat(t_philo *philo)
{
	long last_eat;

	last_eat = print_message(EATING, philo);
	sem_wait(philo->sem_access);
	philo->eating = 1;
	philo->eaten++;
	philo->last_eat = last_eat;
	sem_post(philo->sem_access);
	usleep(philo->data->time_eat * 1000);
	sem_wait(philo->sem_access);
	philo->eating = 0;
	sem_post(philo->sem_access);
}

static int ft_finish(t_philo *philo)
{
	sem_wait(philo->sem_access);
	philo->running = 0;
	sem_post(philo->sem_access);
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
