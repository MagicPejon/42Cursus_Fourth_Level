/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:50 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/20 16:10:08 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	philo_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
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
			if (!philo_isdigit(av[i][j]))
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
	unsigned int	i;

	//incase of high number of philosophers, put start gettimeofday here
	i = 0;
	if (philo_check_error(av) || (ac != 5 && ac != 6))
		philo_print_error(ERR_INPUT);
	philo = malloc(sizeof(t_philo) * philo_atoi(av[1], NULL, NULL));
	if (!philo)
		philo_print_error(ERR_MALLOC);
	table = philo_init(av, philo);
	printf("The inputs are:\n nop:%d\n ttd:%d\n tte:%d\n tts:%d\n goal:%d\n", philo->t_info->nop, philo->t_info->time_to_die, philo->t_info->time_to_eat, philo->t_info->time_to_sleep, philo->t_info->goal);
	while (i < table->nop)
	{
		printf("Philosopher %d has: %d, %d and %d\n", philo[i].id, philo[i].state, philo[i].l_timer, philo[i].meals);
		printf("Fork set: %d\n", table->forks[i]);
		printf("m_fork set: %d\n", table->m_forks[i]);
		printf("Philosopher left: %p and right: %p\n", philo[i].lfork, philo[i].rfork);
		printf("Philosopher mirror left: %p and mirror right: %p\n", philo[i].lmfork, philo[i].rmfork);
		i++;
	}
	philo_summon(philo, table);
	philo_complete(table, philo);
	return (0);
}
