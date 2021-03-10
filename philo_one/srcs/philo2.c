/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:20:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:28:30 by user42           ###   ########.fr       */
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
			if (philo->id)
				lfork = philo->id - 1;
			else 
				lfork = philo->nbrphilos;
			rfork = philo->id;
			pthread_mutex_unlock(&philo->mfork[lfork]);
			pthread_mutex_unlock(&philo->mfork[rfork]);
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
	}
	return (0);
}

int		isliving(t_strct *philo, int lfork, int rfork)
{
	pthread_mutex_lock(&philo->mfork[philo->fork[1]]);
	pthread_mutex_lock(&philo->mfork[philo->fork[0]]);
	printmessage(philo, FORK);
	printmessage(philo, FORK);
	if (isdead(philo, TAKEN))
		return (0);
	gettimeofday(&philo->start, NULL);
	printmessage(philo, EATING);
	issleeping(philo->timetoeat);
	//pthread_mutex_lock(&g_mliving);
	pthread_mutex_unlock(&philo->mfork[philo->fork[0]]);
	pthread_mutex_unlock(&philo->mfork[philo->fork[1]]);
	pthread_mutex_unlock(&g_mliving);
	//pthread_mutex_lock(&g_mliving);
	if (philo->nbrofeat > 0)
		philo->nbrofeat--;
	//pthread_mutex_unlock(&g_mliving);
	printmessage(philo, SLEEPING);
	issleeping(philo->timetosleep);
	if (isdead(philo, NIL))
		return (0);
	printmessage(philo, THINKING);
	return (1);
}

void	*threadproc(void *arg)
{
	int			lfork;
	int			rfork;
	int			ret;
	t_strct			*philo;

	ret = 0;
	initproc(&philo, &lfork, &rfork, arg);
	if (!(philo->id%2))
		usleep(100);
	pthread_mutex_lock(&g_mprint);
	usleep(100);
	gettimeofday(&philo->start, NULL);
	pthread_mutex_unlock(&g_mprint);
	while (1)
	{
		if (!isliving(philo, philo->fork[0], philo->fork[1]))
			return (NULL);
		
	}
	return (NULL);
}
