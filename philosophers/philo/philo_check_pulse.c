/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_pulse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:53:45 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/21 19:33:13 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_check_pulse(t_philo *p, t_time t)
{
	t.p_life = philo_utime(p, t);
	pthread_mutex_lock(&p->t_info->dlock);
	if (t.p_life - t.p_lastate >= p->t_info->time_to_die
		&& p->t_info->philo_dead == false)
	{
		p->state = DEAD;
		p->t_info->philo_dead = true;
		philo_print(p, p->state, t);
	}
	pthread_mutex_unlock(&p->t_info->dlock);
}
