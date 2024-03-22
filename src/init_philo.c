/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:30:56 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/22 17:13:08 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_philo_back(t_philo **philo, t_philo *new)
{
	if (!*philo)
	{
		*philo = new;
		(*philo)->next = new;
		(*philo)->prev = new;
		return ;
	}
	new->next = *philo;
	new->prev = (*philo)->prev;
	(*philo)->prev->next = new;
	(*philo)->prev = new;
}

t_philo	*new_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	pthread_mutex_init(&philo->fork, NULL);
	philo->num_eat = 0;
	philo->is_dead = FALSE;
	philo->is_taken = FALSE;
	philo->num_forks = 0;
	philo->last_meal = 0;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

void	init_all_mutex(void)
{
	pthread_mutex_init(&get_core()->print_status, NULL);
	pthread_mutex_init(&get_core()->dead_mutex, NULL);
	pthread_mutex_init(&get_core()->check_dead_mutex, NULL);
}

t_data	*get_core(void)
{
	static t_data	core;

	return (&core);
}

void	init_philos(void)
{
	int		i;
	t_philo	*philo;

	i = 1;
	philo = NULL;
	while (i <= get_core()->num_philos)
	{
		add_philo_back(&philo, new_philo(i));
		i++;
	}
	get_core()->head = philo;
}
