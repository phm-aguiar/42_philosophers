/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:22:17 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 10:34:11 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	pthread_mutex_lock(&get_mutex()->check_eat_mutex);
	philo->last_meal = get_time(MILLISEC);
	pthread_mutex_unlock(&get_mutex()->check_eat_mutex);
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
	pthread_mutex_lock(&philo->next->fork);
	if (imdead(philo))
		return ;
	print_status(philo, "has taken a fork");
	if (imdead(philo))
		return ;
	pthread_mutex_lock(&philo->fork);
	if (imdead(philo))
		return ;
	print_status(philo, "has taken a fork");
	if (imdead(philo))
		return ;
	pthread_mutex_lock(&get_mutex()->forks_mutex);
	philo->num_forks = 2;
	pthread_mutex_unlock(&get_mutex()->forks_mutex);
	if (imdead(philo))
		return ;
	eating(philo);
}
