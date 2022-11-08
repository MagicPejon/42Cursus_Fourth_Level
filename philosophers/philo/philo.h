/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:35 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/08 15:59:41 by amalbrei         ###   ########.fr       */
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
enum	e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct s_philo{
	int				philo_id;
	int				state;
	unsigned int	l_timer;
}	t_philo;

typedef struct s_table{
	unsigned int	nop;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	unsigned int	goal;
	bool			*forks;
	bool			*p_forks;
	unsigned int	time;
}	t_table;

/* philo.c */
void	philo_print_error(char *err);
int		philo_strlen(char *str);

/* philo_init.c */
void	philo_free(char *err, t_table *table);
int		philo_atoi(char *av, t_table *table);
void	philo_init(char **av, t_table **table);

#endif