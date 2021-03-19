/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:06:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 17:10:03 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		initproc(t_strct **philo, int *lfork, int *rfork, void *arg)
{
	//pthread_mutex_lock(&g_minit);
	//sem_wait((*philo)->semstate);
	printf("its going through\n");
	fflush(stdout);
	*philo = (t_strct*)arg;
	//pthread_mutex_unlock(&g_minit);
	//pthread_mutex_lock(&g_minit);
	*lfork = (*philo)->fork[0];
	*rfork = (*philo)->fork[1];
	gettimeofday(&(*philo)->start, NULL);
	gettimeofday(&(*philo)->end, NULL);
	//pthread_mutex_unlock(&g_minit);
	//sem_post((*philo)->semstate);
	if (!((*philo)->id % 2))
		usleep((*philo)->nbrphilos * 200);
	return (0);
}

void	writing(t_strct *philo, int status, int nil, struct timeval now)
{
	if (!nil || (philo->nbrofeat > 0))
	{
		ft_putstr_fd(ft_itoa(elapsed(*philo->stamp, now)), 1);
		write(1, " Philosopher ", ft_strlen(" Philosopher "));
		write(1, ft_itoa(philo->id), ft_strlen(ft_itoa(philo->id)));
		write(1, " ", 1);
	}
	if (status == FORK && (!nil || philo->nbrofeat))
		write(1, "has taken a fork\n", ft_strlen("has taken a fork\n"));
	else if (status == EATING && (!nil || (philo->nbrofeat > 0)))
		write(1, "is eating\n", ft_strlen("is eating\n"));
	else if (status == SLEEPING && (!nil || (philo->nbrofeat > 0)))
		write(1, "is sleeping\n", ft_strlen("is sleeping\n"));
	else if (status == THINKING && (!nil || (philo->nbrofeat > 0)))
		write(1, "is thinking\n", ft_strlen("is thinking\n"));
	else if (status == DIED && (!nil || (philo->nbrofeat > 0)))
		write(1, "died\n", ft_strlen("died\n"));
}

void	printmessage(t_strct *philo, int status)
{
	int				i;
	static int		nil;
	struct timeval	now;

	//pthread_mutex_lock(&g_mprint);
	sem_wait(philo->semprint);
	gettimeofday(&now, NULL);
	i = philo->id;
	if (nil && (philo->nbrofeat <= 0))
	{
		sem_post(philo->semprint);
		//pthread_mutex_unlock(&g_mprint);
		return ;
	}
	if (status == EATING)
	{
		philo->haseaten = 1;
	}
	writing(philo, status, nil, now);
	if (status == DIED)
		nil = 1;
	sem_post(philo->semprint);
	//pthread_mutex_unlock(&g_mprint);
}

int		dead(t_strct *philo)
{
	gettimeofday(&philo->end, NULL);
	philo->elapsed = (int)((philo->end.tv_usec / 1000) +\
	(philo->end.tv_sec * 1000)) - ((philo->start.tv_usec / 1000) +\
	(philo->start.tv_sec * 1000));
	if (philo->elapsed > philo->timetodie)
	{
		*philo->isdead = 1;
		printmessage(philo, DIED);
		return (1);
	}
	return (0);
}

//int		callfork(t_strct *philo, int status)
//{
//	int i;
//
//	pthread_mutex_lock(&g_minit);
//	i = setforks(philo, TAKEN);
//	pthread_mutex_unlock(&g_minit);
//	return (i);
//}
