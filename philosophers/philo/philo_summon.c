/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_summon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:02:49 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/23 18:20:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	philo_utime(t_philo *person)
{
	gettimeofday(&person->life, NULL);
	person->p_life = (person->life.tv_sec * 1000)
		+ (person->life.tv_usec / 1000);
	person->p_life = person->p_life - person->t_info->p_start;
	return (person->p_life);
}

void	*philo_table(void *philo)
{
	t_philo	*p;

	p = (t_philo *) philo;
	p->p_lastate = 0;
	while (1)
	{
		if (p->id < p->t_info->nop)
		{
			pthread_mutex_lock(p->lffork);
			pthread_mutex_lock(p->rffork);
		}
		else
		{
			pthread_mutex_lock(p->rffork);
			pthread_mutex_lock(p->lffork);
		}
		if (!(*p->lfork) && !(*p->rfork)
			&& (*p->lmfork) != p->id && (*p->rmfork) != p->id)
			philo_chowder(p);
		else
		{
			pthread_mutex_unlock(p->lffork);
			pthread_mutex_unlock(p->rffork);
		}
		pthread_mutex_lock(&p->t_info->dlock);
		if ((p->t_info->philo_dead == true) || (philo_utime(p) - p->p_lastate
				>= p->t_info->time_to_die) || (p->meals == p->t_info->goal))
		{
			pthread_mutex_unlock(&p->t_info->dlock);
			philo_check_pulse(p);
			printf("why you here number %d? is it philo dead %d\n, timer %lu\n, or meals %d = %d\n", p->id, p->t_info->philo_dead, philo_utime(p) - p->p_lastate, p->meals, p->t_info->goal);
			return (NULL);
		}
		pthread_mutex_unlock(&p->t_info->dlock);
	}
	return (NULL);
}

void	philo_summon(t_philo *philo, t_table *table)
{
	unsigned int	i;

	philo_start_clock(philo, table);
	i = -1;
	while (++i < philo->t_info->nop)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_table,
				&philo[i]) != 0)
			philo_free(ERR_THREAD, philo, table);
		usleep(100);
	}
	i = -1;
	while (++i < philo->t_info->nop)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			philo_free(ERR_JOIN, philo, table);
	}
}
