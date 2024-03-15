/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/15 18:02:16 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	philo->is_sleeping = TRUE;
	print_status(philo, "is sleeping");
	usleep(get_core()->time_to_sleep);
	philo->is_sleeping = FALSE;
}

void	eating(t_philo *philo)
{
	philo->is_eating = TRUE;
	usleep(100);
	print_status(philo, "is eating");
	usleep(get_core()->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	philo->is_taken = FALSE;
	philo->num_forks = 0;
	philo->num_eat++;
}

t_bool	fork_next_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	philo->num_forks = 2;
	print_status(philo, "has taken a fork");
	eating(philo);
	return (TRUE);
}

void	*take_fork(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (!pthread_mutex_lock(&philo->fork))
	{
		print_status(philo, "has taken a fork");
	}
	philo->num_forks = 1;
	while (philo->next->num_forks == 2)
	{
		pthread_mutex_unlock(&philo->fork);
		philo->num_forks = 0;
		usleep(100);
	}
	if (philo->next->num_forks == 0)
	{
		fork_next_philo(philo);
	}
	if (philo->is_eating == TRUE)
		sleeping(philo);
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