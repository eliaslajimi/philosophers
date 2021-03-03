/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:06:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:27:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t g_mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex4 = PTHREAD_MUTEX_INITIALIZER;

int		initproc(t_strct **philo, int *lfork, int *rfork, void *arg)
{
	pthread_mutex_lock(&g_mutex1);
	*philo = (t_strct*)arg;
	pthread_mutex_unlock(&g_mutex1);
	pthread_mutex_lock(&g_mutex1);
	*lfork = (*philo)->fork[0];
	*rfork = (*philo)->fork[1];
	gettimeofday(&(*philo)->start, NULL);
	gettimeofday(&(*philo)->end, NULL);
	pthread_mutex_unlock(&g_mutex1);
	return (0);
}

void	printmessage(t_strct *philo, int status)
{
	int				i;
	struct timeval	now;

	pthread_mutex_lock(&g_mutex3);
	gettimeofday(&now, NULL);
	i = philo->id;
	if (status == EATING)
		philo->queue[i] = elapsed(*philo->stamp, now);
	ft_putstr_fd(ft_itoa(elapsed(*philo->stamp, now)), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" ", 1);
	if (status == FORK)
		ft_putstr_fd("has taken a fork\n", 1);
	if (status == EATING)
		ft_putstr_fd("is eating\n", 1);
	if (status == SLEEPING)
		ft_putstr_fd("is sleeping\n", 1);
	if (status == THINKING)
		ft_putstr_fd("is thinking\n", 1);
	if (status == DIED)
		ft_putstr_fd("died\n", 1);
	pthread_mutex_unlock(&g_mutex3);
}

int		checktime(t_strct *philo)
{
	int ret;

	pthread_mutex_lock(&g_mutex4);
	ret = 0;
	if (!*philo->isdead)
	{
		gettimeofday(&philo->end, NULL);
		philo->elapsed = (int)((philo->end.tv_usec / 1000) +\
		(philo->end.tv_sec * 1000)) - ((philo->start.tv_usec / 1000) +\
		(philo->start.tv_sec * 1000));
		if (philo->elapsed > philo->timetodie)
		{
			*philo->isdead = 1;
			printmessage(philo, DIED);
		}
	}
	if (*philo->isdead || philo->nbrofeat == 0)
		ret = -1;
	pthread_mutex_unlock(&g_mutex4);
	return (ret);
}

int		callfork(t_strct *philo, int status)
{
	int i;

	pthread_mutex_lock(&g_mutex1);
	i = setforks(philo, TAKEN);
	pthread_mutex_unlock(&g_mutex1);
	return (i);
}

int		iswaiting(t_strct **philo)
{
	int			lfork;
	int			rfork;
	int			ret;
	static int	odd;

	ret = 1;
	lfork = (*philo)->fork[0];
	rfork = (*philo)->fork[1];
	pthread_mutex_lock(&g_mutex2);
	if (((*philo)->bfork[lfork] == 1 &&\
	(*philo)->bfork[rfork] == 1 && queue(*philo)))
	{
		setforks(*philo, TAKEN);
		ret = 0;
	}
	if (*((*philo)->isdead))
		ret = 0;
	pthread_mutex_unlock(&g_mutex2);
	return (ret);
}
