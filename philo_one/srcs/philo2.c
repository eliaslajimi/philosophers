/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:20:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 00:01:12 by user42           ###   ########.fr       */
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

int		elapsed(struct timeval then, struct timeval now)
{
	int elapsed;

	elapsed = ((now.tv_usec / 1000) + (now.tv_sec * 1000)) -\
	((then.tv_usec / 1000) + (then.tv_sec * 1000));
	return (elapsed);
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

void		takefork(t_strct *philo, int status)
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
	t_strct			*philo;

	ret = 0;
	initproc(&philo, &lfork, &rfork, arg);
	pthread_create(&philo->checktime, NULL, checktime, (void*)philo);
	if (!(philo->id%2))
		usleep(philo->nbrphilos * 200);
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
