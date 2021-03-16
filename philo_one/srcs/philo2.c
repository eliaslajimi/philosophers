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

#include "philo_one.h"

int		isdead(t_strct *philo, int status)
{
	int lfork;
	int rfork;

	if (*philo->isdead)
	{
		if (status == TAKEN)
		{
			pthread_mutex_unlock(&philo->mfork[philo->fork[0]]);
			pthread_mutex_unlock(&philo->mfork[philo->fork[1]]);
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
		pthread_mutex_lock(&philo->mfork[philo->fork[1]]);
		pthread_mutex_lock(&philo->mfork[philo->fork[0]]);
	}
	if (status == FREE)
	{
		pthread_mutex_unlock(&philo->mfork[philo->fork[0]]);
		pthread_mutex_unlock(&philo->mfork[philo->fork[1]]);
	}
}

void	*threadproc(void *arg)
{
	int			lfork;
	int			rfork;
	int			ret;
	t_strct		*philo;

	ret = 0;
	initproc(&philo, &lfork, &rfork, arg);
	while (1)
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
		if (isdead(philo, NIL) && (philo->nbrofeat <= 0))
			return (0);
	}
	return (NULL);
}
