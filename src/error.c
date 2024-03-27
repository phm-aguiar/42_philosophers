/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:04:25 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 10:46:00 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_philo *philo)
{
	t_philo	*tmp;

	philo->prev->next = NULL;
	while (philo)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}

void	error(char *msg)
{
	printf("%sError: %s\n%s", RED, msg, RESET);
	exit(1);
}
