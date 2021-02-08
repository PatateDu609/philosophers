/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:09:10 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/08 22:21:47 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	ft_free_all(t_data *data, int status)
{
	int	i;

	if (data->sem_forks != SEM_FAILED)
		sem_close(data->sem_forks);
	if (data->sem_write != SEM_FAILED)
		sem_close(data->sem_write);
	i = 0;
	while (i < data->nb_philos)
	{
		if (data->sem_access[i] != SEM_FAILED)
			sem_close(data->sem_access[i]);
		i++;
	}
	free(data->sem_access);
	free(data->philosophers);
	free(data);
	return (status);
}
