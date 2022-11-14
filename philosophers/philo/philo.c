/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:50 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/09 19:51:19 by amalbrei         ###   ########.fr       */
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

	if (philo_check_error(av) || (ac != 5 && ac != 6))
		philo_print_error(ERR_INPUT);
	philo = malloc(sizeof(t_philo) * philo_atoi(av[1], NULL));
	if (!philo)
		philo_print_error(ERR_MALLOC);
	philo_init(av, &philo);
	printf("The inputs are:\n nop:%d\n ttd:%d\n tte:%d\n tts:%d\n goal:%d\n", table->nop, table->time_to_die, table->time_to_eat, table->time_to_sleep, table->goal);
	// philo_summon(&table);
	free(table);
	return (0);
}
