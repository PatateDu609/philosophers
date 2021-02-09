/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:12:35 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 16:13:17 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	ft_init_semaphore(t_data *data)
{
	int		i;

	sem_unlink("/forks");
	data->sem_forks = sem_open("/forks", O_CREAT, 0644, data->nb_philos);
	if (data->sem_forks == SEM_FAILED)
		return (0);
	sem_unlink("/finish");
	data->sem_finish = sem_open("/finish", O_CREAT, 0644, 1);
	if (data->sem_finish == SEM_FAILED)
		return (0);
	data->philosophers = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->philosophers)
		return (0);
	data->sem_access = malloc(sizeof(sem_t *) * data->nb_philos);
	if (!data->sem_access)
		return (0);
	memset(data->sem_access, 0, sizeof(sem_t *) * data->nb_philos);
	i = 0;
	while (i < data->nb_philos)
	{
		sem_unlink(get_access(i));
		data->sem_access[i] = sem_open(get_access(i), O_CREAT, 0644, 1);
		if (data->sem_access[i++] == SEM_FAILED)
			return (0);
	}
	return (1);
}

t_philo	*ft_init_philos(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].data = data;
		philos[i].running = 0;
		philos[i].nb = i;
		philos[i].eaten = 0;
		philos[i].last_eat = data->start;
		i++;
	}
	return (philos);
}

int	ft_init(t_data **data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (0);
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->sem_finish = SEM_FAILED;
	(*data)->sem_forks = SEM_FAILED;
	(*data)->sem_access = NULL;
	(*data)->philosophers = NULL;
	(*data)->start = 0;
	(*data)->nb_philos = ft_atoi(av[1]);
	(*data)->time_die = ft_atoi(av[2]);
	(*data)->time_eat = ft_atoi(av[3]);
	(*data)->time_sleep = ft_atoi(av[4]);
	(*data)->nb_eat = -2;
	(*data)->finish = 0;
	if (ac == 6)
		(*data)->nb_eat = ft_atoi(av[5]);
	return ((*data)->nb_philos != -1 && (*data)->time_die != -1
		&& (*data)->nb_eat != -1 && (*data)->time_eat != -1
		&& (*data)->time_sleep != -1);
}
