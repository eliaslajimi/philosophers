/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:20:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 17:06:40 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		isdead(t_strct *philo, int status)
{
	int lfork;
	int rfork;

	if (*philo->isdead)
	{
		if (status == TAKEN)
		{
			sem_post(philo->semfork);
			sem_post(philo->semfork);
		}
		return (1);
	}
	return (0);
}

int		issleeping(int sleep)
{
	struct timeval then;
	struct timeval now;

	gettimeofday(&then, NULL);
	gettimeofday(&now, NULL);
	while (elapsed(then, now) < sleep)
	{
		gettimeofday(&now, NULL);
		usleep(100);
	}
	return (0);
}

void	takefork(t_strct *philo, int status)
{
	if (status == TAKEN)
	{
		sem_wait(philo->semfork);
		sem_wait(philo->semfork);
	}
	if (status == FREE)
	{
		sem_post(philo->semfork);
		sem_post(philo->semfork);
	}
}

int		isalive(t_strct *philo)
{
	if (isdead(philo, NIL) || (philo->nbrofeat == 0))
		if (isdead(philo, NIL) ||\
				(philo->nbrofeat == 0 && (*philo->isdead = 1)))
			return (0);
	return (1);
}

void		*checkdeath(void *arg)
{
	t_strct *philo;

	philo = (t_strct*)arg;
	sem_wait(philo->semdead);
	//sem_wait(philo->semdead);
	*philo->isdead = 1;
	exit(0);
}

int		isliving(t_strct *philo)
{
	int			lfork;
	int			rfork;

	initproc(&philo, &lfork, &rfork);
	pthread_create(&philo->checkdeath, NULL, checkdeath, (void*)philo);
	while (isalive(philo))
	{
		takefork(philo, TAKEN);
		printmessage(philo, FORK);
		printmessage(philo, FORK);
		if (philo->nbrofeat > 0)
			philo->nbrofeat--;
		printmessage(philo, EATING);
		issleeping(philo->timetoeat);
		printmessage(philo, SLEEPING);
		takefork(philo, FREE);
		issleeping(philo->timetosleep);
		printmessage(philo, THINKING);
	}
	exit(0);
}
