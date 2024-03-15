/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:30:56 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/15 16:58:02 by phenriq2         ###   ########.fr       */
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
	philo->is_taken = FALSE;
	philo->is_eating = FALSE;
	philo->is_sleeping = FALSE;
	philo->is_thinking = FALSE;
	philo->is_dead = FALSE;
	philo->num_forks = 0;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
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

void	print_philo(void)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = get_core()->head;
	while (i < get_core()->num_philos)
	{
		printf("================================\n");
		printf("philo %d\n", philos->id);
		printf("philo atual %p\n", philos);
		printf("philo next %p\n", philos->next);
		printf("philo id next %d\n", philos->next->id);
		printf("philo prev %p\n", philos->prev);
		printf("philo id prev %d\n", philos->prev->id);
		philos = philos->next;
		i++;
	}
	i = 0;
}
