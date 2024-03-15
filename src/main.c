/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:47:10 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/15 18:03:00 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(int time_code)
{
	struct timeval	tv;

	(void)time_code;
	if (gettimeofday(&tv, NULL))
		exit(1);
	return ((tv.tv_sec * 1e6) + (tv.tv_usec / 1e6));
}

void	print_status(t_philo *philo, char *status)
{
	get_core()->start_time += 100;
	usleep(100);
	printf("%li %d %s\n", get_core()->start_time, philo->id, status);
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

void	create_threads(t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	while (!get_core()->dead)
	{
		i = 0;
		while (i < get_core()->num_philos)
		{
			pthread_create(&philo->thread, NULL, take_fork, (void *)philo);
			philo = philo->next;
			i++;
		}
		wait_for_threads(philo);
		if (j == 4)
			get_core()->dead = TRUE;
		usleep(100);
		printf("%d\n", j);
		j++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	get_core()->num_philos = atoi(argv[1]);
	get_core()->time_to_die = atoi(argv[2]) * 1000;
	get_core()->time_to_eat = atoi(argv[3]) * 1000;
	get_core()->time_to_sleep = atoi(argv[4]) * 1000;
	if (argc == 6)
		get_core()->num_must_eat = atoi(argv[5]);
	else
		get_core()->num_must_eat = -1;
	init_philos();
	philo = get_core()->head;
	create_threads(philo);
	wait_for_threads(philo);
	return (0);
}
// print_philo();
