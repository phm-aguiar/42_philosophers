/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:30:56 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 17:05:19 by phenriq2         ###   ########.fr       */
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
	philo->num_eat = 0;
	philo->num_forks = 0;
	philo->last_meal = get_time();
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

void	init_all_mutex(void)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = get_core()->head;
	while (i < get_core()->num_philos)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo = philo->next;
		i++;
	}
	pthread_mutex_init(&get_mutex()->print_status, NULL);
	pthread_mutex_init(&get_mutex()->dead_mutex, NULL);
	pthread_mutex_init(&get_mutex()->check_dead_mutex, NULL);
	pthread_mutex_init(&get_mutex()->check_eat_mutex, NULL);
	pthread_mutex_init(&get_mutex()->core_mutex, NULL);
	pthread_mutex_init(&get_mutex()->forks_mutex, NULL);
	pthread_mutex_init(&get_mutex()->time_mutex, NULL);
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
