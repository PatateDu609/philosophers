/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 20:09:10 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/09 04:06:23 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_free_all(t_data *data, int status)
{
	if (data->sem_forks != SEM_FAILED)
		sem_close(data->sem_forks);
	if (data->sem_quota != SEM_FAILED)
		sem_close(data->sem_quota);
	free(data->philosophers);
	free(data);
	return (status);
}
