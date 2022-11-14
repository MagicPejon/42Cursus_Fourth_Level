/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:32:22 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/09 19:53:46 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(char *err, t_table *philo)
{
	free(philo);
	philo_print_error(err);
}

int	philo_atoi(char *av, t_table *table)
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
	if (res > 4294967295 && sign == 1)
		philo_free(ERR_INPUT, table);
	if (res > 4294967295 && sign == -1)
		philo_free(ERR_INPUT, table);
	return (res * sign);
}

void	table_init(char **av, t_philo **philo)
{
	int	i;

	i = 1;
	(*philo)->table_info->nop = philo_atoi(av[i++], *philo);
	(*philo)->table_info->time_to_die = philo_atoi(av[i++], *philo);
	(*philo)->table_info->time_to_eat = philo_atoi(av[i++], *philo);
	(*philo)->table_info->time_to_sleep = philo_atoi(av[i++], *philo);
	if (av[i])
		(*philo)->table_info->goal = philo_atoi(av[i], *philo);
	else
		(*philo)->table_info->goal = 0;
	(*philo)->table_info->philo_dead = false;
}

void	philo_init(char **av, t_philo **philo)
{
	int		i;
	t_table	*table_info;

	i = 0;
	table_info = malloc(sizeof(t_table));
	if (!table_info)
		philo_free(ERR_MALLOC, *philo);
	table_init(av, philo);
}
