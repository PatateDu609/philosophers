/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:25:57 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/07 16:58:50 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

#include "debug.h"

int threads;

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philos;

	int datas = open("/dev/pts/3", O_RDWR);
	write(datas, "\033c\033[3J", 6);
	threads = open("/dev/pts/2", O_RDWR);
	write(threads, "\033c\033[3J", 6);

	init_thread_debug(threads);
	data = NULL;
	if (!ft_init(&data, ac, av))
	{
		free(data);
		return (usage());
	}
	if (!ft_init_mutex(data))
		return (ft_free_all(data, EXIT_FAILURE));
	philos = ft_init_philos(data);
	if (!philos)
		return (ft_free_all(data, EXIT_FAILURE));
	debug(datas, data, philos);

	ft_simulate(data, philos);

	free(philos);

	close(datas);
	close(threads);
	return (ft_free_all(data, EXIT_SUCCESS));
}
