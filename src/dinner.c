/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/18 19:31:42 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->num_forks == 0)
		take_fork(philo);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(get_core()->time_to_sleep);
	thinking(philo);
}

void	eating(t_philo *philo)
{
	if (get_time(MILLISEC) - philo->last_meal > get_core()->time_to_die / 1000)
	{
		philo->is_dead = TRUE;
		get_core()->dead = TRUE;
		print_status(philo, "died");
		return ;
	}
	print_status(philo, "is eating");
	usleep(get_core()->time_to_eat);
	philo->last_meal = get_time(MILLISEC);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	philo->num_forks = 0;
	philo->num_eat++;
	sleeping(philo);
}

void	take_fork(t_philo *philo)
{
	if (philo->is_dead)
		return ;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	print_status(philo, "has taken a fork");
	philo->num_forks = 2;
	eating(philo);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_core()->start_time;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!get_core()->dead)
	{
		take_fork(philo);
	}
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