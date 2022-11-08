/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:32:22 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/08 15:59:36 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(char *err, t_table *table)
{
	free(table);
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

void	philo_init(char **av, t_table **table)
{
	int	i;

	i = 1;

	(*table)->nop = philo_atoi(av[i++], *table);
	(*table)->time_to_die = philo_atoi(av[i++], *table);
	(*table)->time_to_eat = philo_atoi(av[i++], *table);
	(*table)->time_to_sleep = philo_atoi(av[i++], *table);
	if (av[i])
		(*table)->goal = philo_atoi(av[i], *table);
	else
		(*table)->goal = 0;
}
