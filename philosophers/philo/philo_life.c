/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:03:42 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/25 15:02:12 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_snooze(t_philo *p, unsigned int target)
{
	unsigned int	timer;
	unsigned int	new;

	timer = 0;
	new = philo_utime(p);
	while (timer < target)
	{
		usleep(100);
		timer = philo_utime(p) - new;
		if (philo_check_pulse(p))
			break ;
	}
	philo_check_pulse(p);
}

void	philo_thinker(t_philo *p)
{
	if ((p->state != DEAD || p->t_info->philo_dead == false)
		&& (p->meals != p->t_info->goal))
	{
		p->state = THINKING;
		philo_print(p, p->state);
	}
}

void	philo_slumber(t_philo *p)
{
	if ((p->state != DEAD || p->t_info->philo_dead == false)
		&& (p->meals != p->t_info->goal))
	{
		p->state = SLEEPING;
		philo_print(p, p->state);
		philo_snooze(p, p->t_info->time_to_sleep);
		philo_thinker(p);
	}
}

void	philo_chowder(t_philo *p)
{
	if ((p->state != DEAD || p->t_info->philo_dead == false)
		&& (p->meals != p->t_info->goal))
	{
		(*p->lfork) = true;
		(*p->rfork) = true;
		(*p->lmfork) = p->id;
		(*p->rmfork) = p->id;
		philo_unlock_forks(p);
		p->meals++;
		p->p_lastate = philo_utime(p);
		philo_check_pulse(p);
		p->state = EATING;
		philo_print(p, p->state);
		philo_snooze(p, p->t_info->time_to_eat);
		philo_lock_forks(p);
		(*p->lfork) = false;
		(*p->rfork) = false;
		philo_unlock_forks(p);
		philo_slumber(p);
	}
}
