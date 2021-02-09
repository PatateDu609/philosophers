/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:31:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 01:56:49 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

#include "debug.h"

int threads, threads2;

int main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;

	int datas = open("/dev/pts/3", O_RDWR);
	write(datas, "\033c\033[3J", 6);
	threads = open("/dev/pts/2", O_RDWR);
	write(threads, "\033c\033[3J", 6);
	threads2 = open("/dev/pts/5", O_RDWR);
	write(threads2, "\033c\033[3J", 6);

	init_thread_debug(threads);
	init_thread_debug(threads2);
	data = NULL;
	if (!ft_init(&data, ac, av))
	{
		free(data);
		return (usage());
	}
	if (!ft_init_semaphore(data))
		return (ft_free_all(data, EXIT_FAILURE));
	philos = ft_init_philos(data);
	if (!philos)
		return (ft_free_all(data, EXIT_FAILURE));
	debug(datas, data, philos);

	ft_simulate(data, philos);

	free(philos);

	close(threads);
	close(threads2);
	close(datas);
	return ((ft_free_all(data, EXIT_SUCCESS)));
}
