/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:03:42 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/20 16:29:05 by amalbrei         ###   ########.fr       */
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
	}
}

void	philo_thinker(t_philo *p, t_time t)
{
	t.p_life = philo_utime(p, t);
	p->state = THINKING;
	philo_print(p, p->state, t);
}

void	philo_slumber(t_philo *p, t_time t)
{
	t.p_life = philo_utime(p, t);
	p->state = SLEEPING;
	philo_print(p, p->state, t);
	philo_snooze(p, t, p->t_info->time_to_sleep);
	philo_thinker(p, t);
}

void	philo_chowder(t_philo *p, t_time t)
{
	pthread_mutex_lock(&p->t_info->fo_lock[p->id - 1]);
	(*p->lfork) = 1;
	(*p->rfork) = 1;
	(*p->lmfork) = p->id;
	(*p->rmfork) = p->id;
	pthread_mutex_unlock(&p->t_info->fo_lock[p->id - 1]);
	//check if philosopher died function
	t.p_life = philo_utime(p, t);
	p->l_timer += t.p_life;
	p->state = EATING;
	philo_print(p, p->state, t);
	p->l_timer = 0;
	philo_snooze(p, t, p->t_info->time_to_eat);
	p->meals++;
	pthread_mutex_lock(&p->t_info->fo_lock[p->id - 1]);
	(*p->lfork) = 0;
	(*p->rfork) = 0;
	pthread_mutex_unlock(&p->t_info->fo_lock[p->id - 1]);
	philo_slumber(p, t);
}
