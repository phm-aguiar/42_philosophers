/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 17:08:25 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_core()->start_time;
	if (philo->id % 2 == 0)
		usleep(500);
	take_fork(philo);
	return (NULL);
}

void	*dinner_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "has taken a fork");
	usleep(get_core()->time_to_die * 1000);
	return (NULL);
}
