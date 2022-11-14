/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:32:22 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/14 20:59:02 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(char *err, t_philo *philo, t_table *table)
{
	if (table)
		free(table);
	if (philo)
		free(philo);
	philo_print_error(err);
}

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
		philo[i].table_info = table_info;
		philo[i].philo_id = i + 1;
		philo[i].state = SPAWNED;
		philo[i].forks = 0;
		philo[i].p_forks = 0;
		philo[i].l_timer = 0;
		philo[i].meals = 0;
		if (i == table_info->nop - 1)
			philo[i].pos = &philo[0];
		else
			philo[i].pos = &philo[i + 1];
		i++;
	}
	return (table_info);
}
