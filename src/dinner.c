/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/26 17:58:30 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	unlock_forks(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < get_core()->num_philos)
// 	{
// 		pthread_mutex_unlock(&philo->fork);
// 		philo = philo->next;
// 		i++;
// 	}
// }
// if (philo->num_forks == 1)
// 	pthread_mutex_unlock(&philo->fork);
// else if (philo->num_forks == 2)
// {
// 	pthread_mutex_unlock(&philo->fork);
// 	pthread_mutex_unlock(&philo->next->fork);
// }

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_core()->start_time;
	if (philo->id % 2 == 0)
		usleep(10);
	take_fork(philo);
	pthread_mutex_destroy(&philo->fork);
	return (NULL);
}

void	*dinner_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "has taken a fork");
	usleep(get_core()->time_to_die * 1000);
	pthread_mutex_destroy(&philo->fork);
	return (NULL);
}

// t_bool	fork_prev_philo(t_philo *philo)
// {
// 	if (philo->prev->is_taken == TRUE)
// 		return (FALSE);
// 	philo->prev->is_taken = TRUE;
// 	pthread_mutex_lock(&philo->fork_right);
// 	philo->num_forks = 2;
// 	print_status(philo, "has taken a fork");
// 	eating(philo, 2);
// 	return (TRUE);
// }