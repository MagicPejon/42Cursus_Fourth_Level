/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:35 by amalbrei          #+#    #+#             */
/*   Updated: 2022/10/25 19:14:44 by amalbrei         ###   ########.fr       */
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

# define ERR_INPUT "Wrong number of arguments, remember:\n\
./philo no_of_philosophers time_to_die time_to_eat time_to_sleep\
[no_of_philosophers_ate]"
# define ERR_MALLOC "Malloc failed\n"
# define ERR_THREAD "Thread creation failed\n"
# define ERR_JOIN "Thread joining failed\n"
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

typedef struct s_philo{
	unsigned int	philo_id;
	int				state;
}	t_philo;

typedef struct s_table{
	unsigned int	nop;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	unsigned int	goal;
	unsigned int	*forks;
	unsigned int	time;
}	t_table;

#endif