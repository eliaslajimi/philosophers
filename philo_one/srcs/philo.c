/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:06:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 19:27:17 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t g_minit = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mfork = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mliving = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mprint = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mtime = PTHREAD_MUTEX_INITIALIZER;

int		initproc(t_strct **philo, int *lfork, int *rfork, void *arg)
{
	pthread_mutex_lock(&g_minit);
	*philo = (t_strct*)arg;
	pthread_mutex_unlock(&g_minit);
	pthread_mutex_lock(&g_minit);
	*lfork = (*philo)->fork[0];
	*rfork = (*philo)->fork[1];
	gettimeofday(&(*philo)->start, NULL);
	gettimeofday(&(*philo)->end, NULL);
	pthread_mutex_unlock(&g_minit);
	pthread_mutex_lock(&g_minit);
	pthread_mutex_unlock(&g_minit);
	return (0);
}

void	printmessage(t_strct *philo, int status)
{
	int		i;
	static int	nil;
	struct timeval	now;

	gettimeofday(&now, NULL);
	i = philo->id;
	if (nil)
		return ;
	pthread_mutex_lock(&g_mprint);
	if (status == EATING)
		philo->haseaten = 1;
	if (!nil)
	{
		ft_putstr_fd(ft_itoa(elapsed(*philo->stamp, now)), 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(ft_itoa(philo->id), 1);
		ft_putstr_fd(" ", 1);
	}
	if (status == FORK && !nil)
		write(1, "has taken a fork\n", ft_strlen("has taken a fork\n"));
	else if (status == EATING && !nil)
		write(1, "is eating\n", ft_strlen("is eating\n"));
	else if (status == SLEEPING && !nil)
		write(1, "is sleeping\n", ft_strlen("is sleeping\n"));
	else if (status == THINKING && !nil)
		write(1, "is thinking\n", ft_strlen("is thinking\n"));
	else if (status == DIED && !nil)
		write(1, "died\n", ft_strlen("died\n"));
	if (status == DIED)
		nil = 1;
	pthread_mutex_unlock(&g_mprint);
}

void	*checktime(void *arg)
{
	t_strct	*philo;
	int	ret;

	philo = (t_strct*)arg;
	ret = 0;
	while (1)
	{
		pthread_mutex_lock(&g_mtime);
		if (philo->haseaten)
		{
			philo->haseaten = 0;
			gettimeofday(&philo->start, NULL);
			if (philo->nbrofeat > 0)
				philo->nbrofeat--;
		}
		pthread_mutex_unlock(&g_mtime);
		usleep(1000);
		pthread_mutex_lock(&g_mtime);
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
				//printmessage(philo, NIL);
				pthread_mutex_unlock(&g_mtime);
				return (0);
			}
		}
		pthread_mutex_unlock(&g_mtime);
		usleep(2000);
	}
	return (0);
}

int		callfork(t_strct *philo, int status)
{
	int i;

	pthread_mutex_lock(&g_minit);
	i = setforks(philo, TAKEN);
	pthread_mutex_unlock(&g_minit);
	return (i);
}

//int		iswaiting(t_strct **philo)
//{
//	int			lfork;
//	int			rfork;
//	int			ret;
//	static int	odd;
//
//	ret = 1;
//	lfork = (*philo)->fork[0];
//	rfork = (*philo)->fork[1];
//	pthread_mutex_lock(&g_mutex2);
//	if (((*philo)->bfork[lfork] == 1 &&\
//	(*philo)->bfork[rfork] == 1 && queue(*philo)))
//	{
//		setforks(*philo, TAKEN);
//		ret = 0;
//	}
//	if (*((*philo)->isdead))
//		ret = 0;
//	pthread_mutex_unlock(&g_mutex2);
//	return (ret);
//}
