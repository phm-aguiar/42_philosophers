/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:32:36 by phenriq2          #+#    #+#             */
/*   Updated: 2024/04/09 16:43:27 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	print_message(philo, philo->id, PINK "is thinking" RESET);
	usleep(1000);
}

static void	sleeping(t_philo *philo)
{
	print_message(philo, philo->id, BLUE "is sleeping" RESET);
	usleep(philo->time_to_sleep * 1000);
}

static void	eating(t_philo *philo)
{
	print_message(philo, philo->id, YELLOW "is eating" RESET);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep(philo->time_to_eat * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_philos == 1)
	{
		print_message(philo, philo->id, GREEN"has taken a fork"RESET);
		usleep(philo->time_to_die * 1000);
		return (arg);
	}
	while (!dead_loop(philo))
	{
		if (philo->id % 2 == 0)
			safe_lock_fork(philo->r_fork, philo->l_fork, philo);
		else
			safe_lock_fork(philo->l_fork, philo->r_fork, philo);
		eating(philo);
		drop_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}
