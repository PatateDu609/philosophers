/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:12:47 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/23 23:26:05 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_free_all(t_data *data, int status)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->m_forks)
			pthread_mutex_destroy(data->m_forks + i);
		if (data->m_access)
			pthread_mutex_destroy(data->m_access + i++);
	}
	free(data->m_forks);
	free(data->m_access);
	free(data->philosophers);
	free(data);
	return (status);
}
