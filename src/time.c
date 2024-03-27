/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:02:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 17:06:47 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	pthread_mutex_lock(&get_mutex()->time_mutex);
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3);
	pthread_mutex_unlock(&get_mutex()->time_mutex);
	return (time);
}
