/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:51:18 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/20 16:19:38 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_dead(t_philo *philo, t_time t)
{
	printf(RED);
	printf("%lu %d died\n", t.p_life, philo->id);
	printf(DEFAULT);
}

static void	philo_thinking(t_philo *philo, t_time t)
{
	printf(CYAN);
	printf("%lu %d is thinking\n", t.p_life, philo->id);
	printf(DEFAULT);
}

static void	philo_sleeping(t_philo *philo, t_time t)
{
	printf(GREEN);
	printf("%lu %d is sleeping\n", t.p_life, philo->id);
	printf(DEFAULT);
}

static void	philo_eating(t_philo *philo, t_time t)
{
	printf(YELLOW);
	printf("%lu %d has taken a fork\n", t.p_life, philo->id);
	printf("%lu %d is eating\n", t.p_life, philo->id);
	printf(DEFAULT);
}

void	philo_print(t_philo *philo, t_state state, t_time t)
{
	//if (philo->id == 69)
	//	philo_very_curious(philo, state, t);
	pthread_mutex_lock(&philo->t_info->plock);
	if (state == EATING)
		philo_eating(philo, t);
	if (state == SLEEPING)
		philo_sleeping(philo, t);
	if (state == THINKING)
		philo_thinking(philo, t);
	if (state == DEAD)
		philo_dead(philo, t);
	pthread_mutex_unlock(&philo->t_info->plock);
}
