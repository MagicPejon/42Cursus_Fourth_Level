/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:03:42 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/21 19:48:27 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_snooze(t_philo *p, t_time t, unsigned int target)
{
	unsigned int	timer;
	unsigned int	new;

	timer = 0;
	new = philo_utime(p, t);
	while (timer < target)
	{
		usleep(100);
		timer = philo_utime(p, t) - new;
		philo_check_pulse(p, t);
	}
	philo_check_pulse(p, t);
}

void	philo_thinker(t_philo *p, t_time t)
{
	if (p->state != DEAD || p->t_info->philo_dead == false)
	{
		// t.p_life = philo_utime(p, t);
		p->state = THINKING;
		philo_print(p, p->state, t);
	}
}

void	philo_slumber(t_philo *p, t_time t)
{
	if (p->state != DEAD || p->t_info->philo_dead == false)
	{
		// t.p_life = philo_utime(p, t);
		p->state = SLEEPING;
		philo_print(p, p->state, t);
		philo_snooze(p, t, p->t_info->time_to_sleep);
		philo_thinker(p, t);
	}
}

void	philo_chowder(t_philo *p, t_time *t)
{
	if (p->state != DEAD || p->t_info->philo_dead == false)
	{
		(*p->lfork) = true;
		(*p->rfork) = true;
		(*p->lmfork) = p->id;
		(*p->rmfork) = p->id;
		pthread_mutex_unlock(p->lffork);
		pthread_mutex_unlock(p->rffork);
		p->meals++;
		t->p_lastate = philo_utime(p, *t);
		philo_check_pulse(p, *t);
		p->state = EATING;
		philo_print(p, p->state, *t);
		philo_snooze(p, *t, p->t_info->time_to_eat);
		pthread_mutex_lock(p->lffork);
		pthread_mutex_lock(p->rffork);
		(*p->lfork) = false;
		(*p->rfork) = false;
		pthread_mutex_unlock(p->lffork);
		pthread_mutex_unlock(p->rffork);
		philo_slumber(p, *t);
	}
	//make sure all philosophers done eating when goal is met
	//philosophers die at 410, why?
}
