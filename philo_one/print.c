/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:26:03 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 17:02:12 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static char		*ft_event_to_string(t_events event)
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
	return ("Unknown action");
}

long			print_message(t_events event, t_philo *philo)
{
	long	ts;

	ts = ft_timestamp(philo->data);
	if (philo->data->finish)
		return (ts);
	printf("%ld %d %s\n", ts, philo->nb, ft_event_to_string(event));
	return (ts);
}
