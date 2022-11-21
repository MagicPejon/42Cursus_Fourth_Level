/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_summon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:02:49 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/21 19:40:06 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_utime(t_philo *person, t_time t)
{
	gettimeofday(&person->life, NULL);
	t.p_life = (person->life.tv_sec * 1000) + (person->life.tv_usec / 1000);
	t.p_life = t.p_life - t.p_start;
	return (t.p_life);
}

void	*philo_table(void *philo)
{
	t_time	t;
	t_philo	*p;

	p = (t_philo *) philo;
	gettimeofday(&p->start, NULL);
	t.p_start = (p->start.tv_sec * 1000) + (p->start.tv_usec / 1000);
	t.p_life = philo_utime(p, t);
	t.p_lastate = 0;
	//Soft code for one philosophor
	while (p->t_info->philo_dead == false
		&& philo_utime(p, t) - t.p_lastate < p->t_info->time_to_die
		&& p->meals != p->t_info->goal)
	{
		pthread_mutex_lock(p->lffork);
		pthread_mutex_lock(p->rffork);
		if (!(*p->lfork) && !(*p->rfork)
			&& (*p->lmfork) != p->id && (*p->rmfork) != p->id)
			philo_chowder(p, &t);
		else
		{
			pthread_mutex_unlock(p->lffork);
			pthread_mutex_unlock(p->rffork);
		}
		usleep(100);
	}
	printf("why you here number %d? is it philo dead %d\n, timer %lu\n, or meals %d = %d\n", p->id, p->t_info->philo_dead, philo_utime(p, t) - t.p_lastate, p->meals, p->t_info->goal);
	philo_check_pulse(p, t);
	return (NULL);
}

void	philo_summon(t_philo *philo, t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < philo->t_info->nop)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_table,
				&philo[i]) != 0)
			philo_free(ERR_THREAD, philo, table);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < philo->t_info->nop)
	{
		if (pthread_join(philo[i++].thread, NULL) != 0)
			philo_free(ERR_JOIN, philo, table);
	}
}
