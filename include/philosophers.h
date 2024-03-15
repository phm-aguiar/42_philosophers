/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:46:33 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/15 17:40:54 by phenriq2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // Para funções relacionadas a threads
# include <stdio.h>    // Para printf
# include <stdlib.h>   // Para malloc e free
# include <string.h>   // Para memset
# include <sys/time.h> // Para gettimeofday
# include <unistd.h>   // Para write e usleep

typedef struct s_philo	t_philo;

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		fork;
	// pthread_mutex_t		fork_right;
	int					num_eat;
	t_bool				is_taken;
	t_bool				is_eating;
	t_bool				is_sleeping;
	t_bool				is_thinking;
	t_bool				is_dead;
	int					num_forks;
	t_philo				*next;
	t_philo				*prev;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_must_eat;
	long				start_time;
	t_bool				dead;
	t_philo				*head;
}						t_data;

t_data					*get_core(void);
void					print_philo(void);
void					init_philos(void);
t_philo					*new_philo(int id);
void					add_philo_back(t_philo **philo, t_philo *new);

// dinner.c

void					*take_fork(void *arg);
void					eating(t_philo *philo);
t_bool					fork_next_philo(t_philo *philo);

// print_status.c

void					print_status(t_philo *philo, char *status);

#endif // PHILOSOPHERS_H
