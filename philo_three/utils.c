/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:03:38 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 17:21:25 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long	ft_timestamp(t_data *data)
{
	struct timeval		tv;
	long				timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
	if (data)
		return (timestamp - data->start);
	return (timestamp);
}

int	ft_atoi(char *str)
{
	int		result;

	result = 0;
	while ('0' <= *str && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str || result < 0)
		return (-1);
	return (result);
}

int	usage(void)
{
	write(2, "Usage: number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 112);
	return (EXIT_FAILURE);
}
