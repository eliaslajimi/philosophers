/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:23:32 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 17:06:05 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*eating(void *arg)
{
	t_strct *philo;

	philo = (t_strct*)arg;
	while (1)
	{
		if (philo->haseaten)
		{
			philo->haseaten = 0;
			gettimeofday(&philo->start, NULL);
		}
		if (!*philo->isdead)
			if (dead(philo))
				return (0);
		usleep(2000);
	}
	exit(0);
}

void	*wrapper(void *arg)
{
	t_strct *philo;

	philo = (t_strct*)arg;
	sem_wait(philo->semdead);
	sem_post(philo->semdead);
	*(philo->isdead) = 1;
	exit(0);
}
