/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:31 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/22 17:19:22 by phenriq2         ###   ########.fr       */
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
// if (philo->num_forks == 1)
// 	pthread_mutex_unlock(&philo->fork);
// else if (philo->num_forks == 2)
// {
// 	pthread_mutex_unlock(&philo->fork);
// 	pthread_mutex_unlock(&philo->next->fork);
// }

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
	pthread_mutex_lock(&get_core()->dead_mutex);
	if (get_time(MILLISEC) - philo->last_meal >= get_core()->time_to_die)
	{
		philo->is_dead = TRUE;
		get_core()->dead = TRUE;
		print_status(philo, "died");
		pthread_mutex_unlock(&get_core()->dead_mutex);
		unlock_forks(philo);
		return (TRUE);
	}
	pthread_mutex_unlock(&get_core()->dead_mutex);
	return (FALSE);
}

void	thinking(t_philo *philo)
{
	if (imdead(philo))
		return ;
	print_status(philo, "is thinking");
	if (philo->num_forks == 0)
		take_fork(philo);
}

void	sleeping(t_philo *philo)
{
	if (imdead(philo))
		return ;
	print_status(philo, "is sleeping");
	if (imdead(philo))
		return ;
	usleep(get_core()->time_to_sleep);
	if (imdead(philo))
		return ;
	thinking(philo);
}

void	eating(t_philo *philo)
{
	if (imdead(philo))
		return ;
	print_status(philo, "is eating");
	if (imdead(philo))
		return ;
	usleep(get_core()->time_to_eat);
	if (imdead(philo))
		return ;
	philo->last_meal = get_time(MILLISEC);
	if (imdead(philo))
		return ;
	pthread_mutex_unlock(&philo->fork);
	if (imdead(philo))
		return ;
	pthread_mutex_unlock(&philo->next->fork);
	if (imdead(philo))
		return ;
	philo->num_forks = 0;
	philo->num_eat++;
	if (imdead(philo))
		return ;
	sleeping(philo);
}

void	take_fork(t_philo *philo)
{
	if (imdead(philo))
		return ;
	pthread_mutex_lock(&philo->fork);
	if (imdead(philo))
		return ;
	print_status(philo, "has taken a fork");
	if (imdead(philo))
		return ;
	pthread_mutex_lock(&philo->next->fork);
	if (imdead(philo))
		return ;
	print_status(philo, "has taken a fork");
	if (imdead(philo))
		return ;
	philo->num_forks = 2;
	if (imdead(philo))
		return ;
	eating(philo);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_core()->start_time;
	if (philo->id % 2 == 0)
		usleep(1000);
	take_fork(philo);
	pthread_mutex_destroy(&philo->fork);
	return (NULL);
}

void	*dinner_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_core()->start_time;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, "has taken a fork");
	usleep(get_core()->time_to_die * 1000);
	if (imdead(philo))
		return (NULL);
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