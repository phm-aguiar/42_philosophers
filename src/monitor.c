/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:15:04 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 10:54:26 by phenriq2         ###   ########.fr       */
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
	t_bool	dead;

	pthread_mutex_lock(&get_mutex()->check_dead_mutex);
	dead = get_core()->dead;
	pthread_mutex_unlock(&get_mutex()->check_dead_mutex);
	if (dead == TRUE)
	{
		unlock_forks(philo);
		return (TRUE);
	}
	if (philo->num_eat == 4)
	{
		pthread_mutex_lock(&get_mutex()->dead_mutex);
		get_core()->dead = TRUE;
		pthread_mutex_unlock(&get_mutex()->dead_mutex);
		print_status(philo, "is full");
		unlock_forks(philo);
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_bool	time_to_die;

	philo = (t_philo *)arg;
	return (NULL);
	while (get_core()->dead == FALSE)
	{
		pthread_mutex_lock(&get_mutex()->dead_mutex);
		time_to_die = get_time(MILLISEC)
			- philo->last_meal >= get_core()->time_to_die;
		pthread_mutex_unlock(&get_mutex()->dead_mutex);
		if (time_to_die)
		{
			pthread_mutex_lock(&get_mutex()->dead_mutex);
			get_core()->dead = TRUE;
			pthread_mutex_unlock(&get_mutex()->dead_mutex);
			print_status(philo, "died");
			break ;
		}
		philo = philo->next;
	}
	return (NULL);
}
