/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:50 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/23 17:18:01 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start_clock(t_philo *p, t_table *t)
{
	gettimeofday(&p->start, NULL);
	t->p_start = (p->start.tv_sec * 1000) + (p->start.tv_usec / 1000);
}

int	philo_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	philo_print_error(char *err)
{
	write(2, err, philo_strlen(err));
	exit (1);
}

static int	philo_check_error(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= 48 && av[i][j] <= 57))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_table			*table;

	if (philo_check_error(av) || (ac != 5 && ac != 6))
		philo_print_error(ERR_INPUT);
	philo = malloc(sizeof(t_philo) * philo_atoi(av[1], NULL, NULL));
	if (!philo)
		philo_print_error(ERR_MALLOC);
	table = philo_init(av, philo);
	philo_summon(philo, table);
	philo_complete(table, philo);
	return (0);
}
