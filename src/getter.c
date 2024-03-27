/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:25:02 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 10:50:44 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*get_core(void)
{
	static t_data	core;

	pthread_mutex_lock(&get_mutex()->core_mutex);
	pthread_mutex_unlock(&get_mutex()->core_mutex);
	return (&core);
}

t_mutex	*get_mutex(void)
{
	static t_mutex	mutex;

	return (&mutex);
}
