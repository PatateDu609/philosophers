/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:03:38 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/08 22:17:11 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

char	*get_access(int i)
{
	int			index;
	static char	name[10];

	memset(name, 0, 10);
	index = 0;
	name[index++] = '/';
	name[index++] = 'a';
	name[index++] = 'c';
	name[index++] = 'c';
	name[index++] = 'e';
	name[index++] = 's';
	name[index++] = 's';
	memset(name + index, '0', sizeof(char) * 3);
	index += 2;
	name[index--] = (i % 10) + 48;
	while (i / 10)
	{
		i /= 10;
		name[index--] = (i % 10) + 48;
	}
	return (name);
}
