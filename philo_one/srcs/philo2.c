/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:20:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 18:27:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int		isliving(s_strct *philo, int lfork, int rfork)
{
	printmessage(philo, FORK);
	pthread_mutex_lock(&philo->mfork[lfork]);
	pthread_mutex_lock(&philo->mfork[rfork]);
	printmessage(philo, EATING);
	if (checktime(philo))
	{
		pthread_mutex_unlock(&philo->mfork[lfork]);
		pthread_mutex_unlock(&philo->mfork[rfork]);
		return (0);
	}
	gettimeofday(&philo->start, NULL);
	issleeping(philo->timetoeat);
	pthread_mutex_unlock(&philo->mfork[lfork]);
	pthread_mutex_unlock(&philo->mfork[rfork]);
	pthread_mutex_lock(&g_mutex2);
	setforks(philo, FREE);
	pthread_mutex_unlock(&g_mutex2);
	if (philo->nbrofeat > 0)
		philo->nbrofeat--;
	printmessage(philo, SLEEPING);
	issleeping(philo->timetosleep);
	if (checktime(philo))
		return (0);
	printmessage(philo, THINKING);
	return (1);
}

void	*threadproc(void *arg)
{
	int			lfork;
	int			rfork;
	int			ret;
	s_strct		*philo;

	ret = 0;
	initproc(&philo, &lfork, &rfork, arg);
	if ((philo->id + 1) % 2)
		usleep(100);
	while (1)
	{
		while (iswaiting(&philo))
			if (checktime(philo))
				return (NULL);
		if (!isliving(philo, lfork, rfork))
			return (NULL);
	}
	return (NULL);
}
