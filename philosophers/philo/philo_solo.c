/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_solo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:01 by amalbrei          #+#    #+#             */
/*   Updated: 2022/11/25 15:09:55 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_fork(t_philo *p)
{
	printf(RED);
	printf("%lu ", philo_utime(p));
	printf(YELLOW);
	printf("%d ", p->id);
	printf(GREEN);
	printf("has ");
	printf(BLUE);
	printf("taken ");
	printf(PURPLE);
	printf("a fork\n");
	printf(DEFAULT);
}

void	philo_solo(t_philo *p)
{
	philo_fork(p);
	philo_snooze(p, p->t_info->time_to_die);
}
