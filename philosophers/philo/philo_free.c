/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:59:06 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/21 17:22:52 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(char *err, t_philo *philo, t_table *table)
{
	unsigned int	i;

	i = 0;
	if (table)
	{
		if (table->forks)
			free(table->forks);
		if (table->m_forks)
			free(table->m_forks);
		if (table->fo_lock)
		{
			while (i < table->nop)
				pthread_mutex_destroy(&table->fo_lock[i]);
			free(table->fo_lock);
		}
		free(table);
	}
	if (philo)
		free(philo);
	philo_print_error(err);
}

void	philo_complete(t_table *table, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < table->nop)
		pthread_mutex_destroy(&table->fo_lock[i++]);
	pthread_mutex_destroy(&table->dlock);
	pthread_mutex_destroy(&table->plock);
	free(table->forks);
	free(table->m_forks);
	free(table->fo_lock);
	free(table);
	free(philo);
}
