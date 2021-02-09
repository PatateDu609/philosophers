/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:31:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 17:34:39 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;

	data = NULL;
	if (!ft_init(&data, ac, av))
	{
		free(data);
		return (usage());
	}
	if (!ft_init_semaphore(data))
		return (ft_free_all(data, EXIT_FAILURE));
	if (!ft_init_philos(data, &philos))
		return (ft_free_all(data, EXIT_FAILURE));
	ft_simulate(data, philos);
	free(philos);
	return ((ft_free_all(data, EXIT_SUCCESS)));
}
