/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:26:03 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 20:02:12 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static char	*ft_event_to_string(t_events event)
{
	if (event == DIED)
		return ("died");
	if (event == TAKEN_FORK)
		return ("has taken a fork");
	if (event == SLEEPING)
		return ("is sleeping");
	if (event == EATING)
		return ("is eating");
	if (event == THINKING)
		return ("is thinking");
	return (NULL);
}

void	print_message(t_events event, t_philo *philo)
{
	long	ts;

	ts = ft_timestamp(philo->data);
	pthread_mutex_lock(&philo->data->m_write);
	printf("%ld %d %s\n", ts, philo->nb, ft_event_to_string(event));
	pthread_mutex_unlock(&philo->data->m_write);
}
