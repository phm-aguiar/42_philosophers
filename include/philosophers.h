/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phenriq2 <phenriq2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:46:33 by phenriq2          #+#    #+#             */
/*   Updated: 2024/03/27 17:12:26 by phenriq2         ###   ########.fr       */
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
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BLACK "\033[0;30m"
# define RESET "\033[0m"

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
	long				last_meal;
	long				time_to_sleep;
	int					num_eat;
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
	t_bool				printed;
	t_philo				*head;
}						t_data;

typedef struct s_mutex
{
	pthread_mutex_t		print_status;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		check_dead_mutex;
	pthread_mutex_t		check_eat_mutex;
	pthread_mutex_t		core_mutex;
	pthread_mutex_t		forks_mutex;
	pthread_mutex_t		time_mutex;
}						t_mutex;

t_data					*get_core(void);
void					init_philos(void);
t_philo					*new_philo(int id);
void					add_philo_back(t_philo **philo, t_philo *new);

// dinner.c

void					take_fork(t_philo *philo);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);
void					*dinner(void *arg);
t_bool					imdead(t_philo *philo);
void					unlock_forks(t_philo *philo);
void					*monitor(void *arg);
t_mutex					*get_mutex(void);
void					free_all(t_philo *philo);

// print_status.c

void					print_status(t_philo *philo, char *status);

// time.c

long					get_time(void);

// error.c

void					error(char *msg);

void					init_all_mutex(void);
void					*dinner_solo(void *arg);

#endif // PHILOSOPHERS_H
