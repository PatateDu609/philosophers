/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:12:35 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 13:40:56 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_init(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	data->nb_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->nb_eat = -2;
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	return (data->nb_philos != -1 && data->time_die != -1 && data->nb_eat != -1
		&& data->time_eat != -1 && data->time_sleep != -1);
}
