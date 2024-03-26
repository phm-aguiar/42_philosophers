/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:15:04 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/26 18:03:52 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < get_core()->num_philos)
	{
		pthread_mutex_unlock(&philo->fork);
		philo = philo->next;
		i++;
	}
}

t_bool	imdead(t_philo *philo)
{
	pthread_mutex_lock(&get_core()->check_dead_mutex);
	if (get_core()->dead == TRUE)
	{
		pthread_mutex_unlock(&get_core()->check_dead_mutex);
		unlock_forks(philo);
		return (TRUE);
	}
	pthread_mutex_unlock(&get_core()->check_dead_mutex);
	return (FALSE);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_core()->dead == FALSE)
	{
		if (imdead(philo))
			break ;
		if (get_time(MILLISEC) - philo->last_meal >= get_core()->time_to_die)
		{
			philo->is_dead = TRUE;
			get_core()->dead = TRUE;
			print_status(philo, "died");
			break ;
		}
		philo = philo->next;
	}
	return (NULL);
}
