/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:35:49 by phenriq2          #+#    #+#             */
/*   Updated: 2024/04/09 16:33:32 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_lock_fork(pthread_mutex_t *fork, pthread_mutex_t *fork2,
		t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_message(philo, philo->id, GREEN "has taken a fork" RESET);
	pthread_mutex_lock(fork2);
	print_message(philo, philo->id, GREEN "has taken a fork" RESET);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
