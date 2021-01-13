/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:25:57 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 21:09:14 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_philo(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_action(philo, THINKING);
		ft_action(philo, TAKE_FORK);
		ft_action(philo, EAT);
		ft_action(philo, LEAVE_FORK);
		ft_action(philo, SLEEP);
	}
	return (NULL);
}

static void	ft_simulate(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	data->start = ft_timestamp(NULL);
	while (i < data->nb_philos)
	{
		pthread_create(data->philosophers + i, NULL, ft_philo, philos + i);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;

	if (!ft_init(&data, ac, av))
		return (usage());
	if (!ft_init_mutex(&data))
		return (ft_free_all(&data, EXIT_FAILURE));
	philos = ft_init_philos(&data);
	if (!philos)
		return (ft_free_all(&data, EXIT_FAILURE));
	printf("data : %p\n", &data);
	printf("forks : %p\n", data.m_forks);
	printf("philosophers : %p\n", data.philosophers);
	printf("nb_philos : %d\n", data.nb_philos);
	printf("time_die : %d\n", data.time_die);
	printf("time_sleep : %d\n", data.time_sleep);
	printf("time_eat : %d\n", data.time_eat);
	printf("nb_eat : %d\n", data.nb_eat);

	printf("philos : %p\n", philos);
	for (int i = 0; i < data.nb_philos; i++)
		printf("philos %d : nb = %d, data = %p\n", i, (philos + i)->nb, (philos + i)->data);
	ft_simulate(&data, philos);
	free(philos);
	return (ft_free_all(&data, EXIT_SUCCESS));
}
