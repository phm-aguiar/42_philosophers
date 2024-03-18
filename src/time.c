/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:02:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/18 17:10:01 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(t_time unit_of_measurement)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error ("Gettimeofday failed.");
	if (SECOND == unit_of_measurement)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISEC == unit_of_measurement)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSEC == unit_of_measurement)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error("Wrong input to gettime");
	return (-1);
}
