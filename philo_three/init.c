/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:12:35 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 04:06:45 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	data->sem_forks = sem_open("/forks", O_CREAT, 0644, data->nb_philos);
	if (data->sem_forks == SEM_FAILED)
		return (0);
	sem_unlink("/quota");
	data->sem_quota = sem_open("/quota", O_CREAT, 0644, data->nb_philos);
	if (data->sem_quota == SEM_FAILED)
		return (0);
	data->philosophers = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->philosophers)
		return (0);
	return (1);
}

int	ft_init_philos(t_data *data, t_philo **philos)
{
	int			i;

	*philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (0);
	i = 0;
	memset(*philos, 0, sizeof(t_philo) * data->nb_philos);
	while (i < data->nb_philos)
	{
		(*philos)[i].running = 0;
		(*philos)[i].data = data;
		(*philos)[i].nb = i;
		(*philos)[i].eaten = 0;
		(*philos)[i].last_eat = data->start;
		sem_unlink(get_access(i));
		(*philos)[i].sem_access = sem_open(get_access(i), O_CREAT, 0664, 1);
		if ((*philos)[i].sem_access == SEM_FAILED)
			return (0);
		i++;
	}
	return (1);
}

int	ft_init(t_data **data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->sem_quota = SEM_FAILED;
	(*data)->sem_forks = SEM_FAILED;
	(*data)->philosophers = NULL;
	(*data)->nb_philos = ft_atoi(av[1]);
	(*data)->time_die = ft_atoi(av[2]);
	(*data)->time_eat = ft_atoi(av[3]);
	(*data)->time_sleep = ft_atoi(av[4]);
	(*data)->nb_eat = -2;
	(*data)->start = 0;
	(*data)->finish = 0;
	if (ac == 6)
		(*data)->nb_eat = ft_atoi(av[5]);
	return ((*data)->nb_philos != -1 && (*data)->time_die != -1
		&& (*data)->nb_eat != -1 && (*data)->time_eat != -1
		&& (*data)->time_sleep != -1);
}
