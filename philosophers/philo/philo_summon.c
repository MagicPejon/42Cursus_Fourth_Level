/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_summon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:02:49 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/18 20:09:43 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	philo_utime(t_philo *person, unsigned int p_start)
{
	unsigned int	p_life;

	gettimeofday(&person->life, NULL);
	p_life = (person->life.tv_sec * 1000) + (person->life.tv_usec / 1000);
	p_life = p_life - p_start;
	return (p_life);
}

void	*philo_table(void *philo)
{
	int		p_start;
	int		p_life;
	t_philo	*person;

	person = (t_philo *) philo;
	gettimeofday(&person->start, NULL);
	p_start = (person->start.tv_sec * 1000) + (person->start.tv_usec / 1000);
	while (person->table_info->philo_dead == false || p_life == person->l_timer)
	{
		p_life = philo_utime(person, p_start);
	}
	//make a to die function
	return ((void *) person);
}

void	philo_summon(t_philo *philo, t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < philo->table_info->nop)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_table,
				&philo[i]) != 0)
			philo_free(ERR_THREAD, philo, table);
		i++;
	}
	i = 0;
	while (i < philo->table_info->nop)
	{
		if (pthread_join(philo[i++].thread, NULL) != 0)
			philo_free(ERR_JOIN, philo, table);
	}
}
