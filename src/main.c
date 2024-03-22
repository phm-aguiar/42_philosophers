/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:47:10 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/22 16:56:14 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *status)
{
	long	time;

	time = get_time(MILLISEC) - get_core()->start_time;
	pthread_mutex_lock(&get_core()->print_status);
	printf("%li %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&get_core()->print_status);
}

void	wait_for_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < get_core()->num_philos)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}

// pthread_create(&get_core()->monitor, NULL, monitor, (void *)philo);
void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	get_core()->start_time = get_time(MILLISEC);
	if (get_core()->num_philos == 1)
	{
		pthread_create(&philo->thread, NULL, dinner_solo, (void *)philo);
		pthread_join(philo->thread, NULL);
		return ;
	}
	while (i < get_core()->num_philos)
	{
		pthread_create(&philo->thread, NULL, dinner, (void *)philo);
		philo = philo->next;
		i++;
	}
	wait_for_threads(philo);
}
// wait_for_threads(philo);

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	get_core()->num_philos = atoi(argv[1]);
	get_core()->time_to_die = atoi(argv[2]);
	get_core()->time_to_eat = atoi(argv[3]) * 1000;
	get_core()->time_to_sleep = atoi(argv[4]) * 1000;
	init_philos();
	init_all_mutex();
	philo = get_core()->head;
	create_threads(philo);
	return (0);
}
// print_philo();
