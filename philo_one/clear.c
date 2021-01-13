/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:12:47 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/13 20:17:43 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_free_all(t_data *data, int status)
{
	int		i;

	i = 0;
	if (data->m_forks)
		while (i < data->nb_philos)
			pthread_mutex_destroy(data->m_forks + i++);
	free(data->m_forks);
	pthread_mutex_destroy(&data->m_run);
	pthread_mutex_destroy(&data->m_write);
	free(data->philosophers);
	return (status);
}
