/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:32:22 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/18 20:21:09 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(char *av, t_philo *philo, t_table *table)
{
	int		sign;
	size_t	i;
	size_t	res;

	i = 0;
	sign = 1;
	res = 0;
	while (av[i] == ' ' || av[i] == '\f' || av[i] == '\n'
		|| av[i] == '\r' || av[i] == '\t' || av[i] == '\v')
		i++;
	if (av[i] == '+' || av[i] == '-')
	{
		if (av[i++] == '-')
			sign *= -1;
	}
	while (av[i] >= '0' && av[i] <= '9')
	{
		res = (res * 10) + (av[i++] - '0');
	}
	if ((res > 4294967295 && sign == 1) || res == 0)
		philo_free(ERR_INPUT, philo, table);
	if ((res > 4294967295 && sign == -1) || res == 0)
		philo_free(ERR_INPUT, philo, table);
	return (res * sign);
}

void	fork_init(t_philo *philo, t_table **table)
{
	unsigned int	i;

	(*table)->forks = malloc(sizeof((*table)->nop));
	if (!(*table)->forks)
		philo_free(ERR_MALLOC, philo, (*table));
	(*table)->p_forks = malloc(sizeof((*table)->nop));
	if (!(*table)->p_forks)
		philo_free(ERR_MALLOC, philo, (*table));
	(*table)->fo_lock = malloc(sizeof((*table)->nop));
	if (!(*table)->fo_lock)
		philo_free(ERR_MALLOC, philo, (*table));
	i = 0;
	while (i < (*table)->nop)
	{
		(*table)->forks[i] = false;
		(*table)->p_forks[i] = 0;
		pthread_mutex_init(&(*table)->fo_lock[i++], NULL);
	}
}

t_table	*table_init(char **av, t_philo *philo, t_table *table)
{
	int	i;

	i = 1;
	table->nop = philo_atoi(av[i++], philo, table);
	table->time_to_die = philo_atoi(av[i++], philo, table);
	table->time_to_eat = philo_atoi(av[i++], philo, table);
	table->time_to_sleep = philo_atoi(av[i++], philo, table);
	if (av[i])
		table->goal = philo_atoi(av[i], philo, table);
	else
		table->goal = 0;
	table->philo_dead = false;
	fork_init(philo, &table);
	pthread_mutex_init(&table->dlock, NULL);
	pthread_mutex_init(&table->plock, NULL);
	return (table);
}

t_table	*philo_init(char **av, t_philo *philo)
{
	unsigned int		i;
	t_table				*table_info;

	i = 0;
	table_info = malloc(sizeof(t_table));
	if (!table_info)
		philo_free(ERR_MALLOC, philo, table_info);
	table_info = table_init(av, philo, table_info);
	while (i < table_info->nop)
	{
		philo[i].philo_id = i + 1;
		philo[i].state = SPAWNED;
		philo[i].l_timer = table_info->time_to_die;
		philo[i].meals = 0;
		philo[i].table_info = table_info;
		if (i == table_info->nop - 1)
			philo[i].pos = &philo[0];
		else
			philo[i].pos = &philo[i + 1];
		i++;
	}
	return (table_info);
}
