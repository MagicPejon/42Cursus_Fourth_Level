/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:35 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/18 20:20:15 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* malloc, free and exit */
# include <stdlib.h>

/* write */
# include <unistd.h>

/* thread commands */
# include <pthread.h>

/* gettimeofday */
# include <sys/time.h>

/* printf */
# include <stdio.h>

/* for boolean stuff*/
# include <stdbool.h>

# define ERR_INPUT "Wrong number of arguments or invalid inputs, remember:\n\
./philo no_of_philosophers time_to_die time_to_eat time_to_sleep \
[no_of_philosophers_ate]\n"
# define ERR_MALLOC "Malloc failed\n"
# define ERR_THREAD "Thread creation failed\n"
# define ERR_JOIN "Thread joining failed\n"

// # define EATING 0
// # define SLEEPING 1
// # define THINKING 2
// # define DEAD 3
typedef enum e_philo_state
{
	SPAWNED,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef struct s_philo{
	unsigned int	philo_id;
	t_state			state;
	unsigned int	l_timer;
	unsigned int	meals;
	pthread_t		thread;
	struct timeval	start;
	struct timeval	life;
	struct s_table	*table_info;
	struct s_philo	*pos;
}	t_philo;

typedef struct s_table{
	unsigned int	nop;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	unsigned int	goal;
	unsigned int	*p_forks;
	bool			philo_dead;
	bool			*forks;
	pthread_mutex_t	*fo_lock;
	pthread_mutex_t	dlock;
	pthread_mutex_t	plock;
}	t_table;

/* philo.c */
void	philo_print_error(char *err);
int		philo_strlen(char *str);

/* philo_init.c */
int		philo_atoi(char *av, t_philo *philo, t_table *table);
void	fork_init(t_philo *philo, t_table **table);
t_table	*table_init(char **av, t_philo *philo, t_table *table);
t_table	*philo_init(char **av, t_philo *philo);

/* philo_free.c */
void	philo_free(char *err, t_philo *philo, t_table *table);
void	philo_complete(t_table *table, t_philo *philo);

/* philo_summon.c */
void	philo_summon(t_philo *philo, t_table *table);

#endif