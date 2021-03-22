/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:49:34 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 16:55:57 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		initiateforks(t_strct *philo, int nbrphilos)
{
	static int	ret;
	pthread_t	timer;
	pthread_t	thread[nbrphilos];

	givesem(philo);
	forkcreate(philo);
	waitfork(philo);
	freestruct(philo);
	return (ret);
}

int		waitfork(t_strct *philo)
{
	static int i;

	while (i < philo[i].nbrphilos)
	{
		 waitpid(philo[i++].pid, NULL, 0);
	}
	return (0);
}

int		forkcreate(t_strct *philo)
{
	static int i;

	while (i < philo->nbrphilos)
	{
		if ((philo[i].pid = fork()) == -1)
				return (-1);
		if (!philo[i].pid)
		{
		printf("philo->id is %d, pid is %d\n", philo[i].id, philo[i].pid);
		fflush(stdout);
			isliving(philo);
		}
		i++;
	}
	return (0);
}

int		givesem(t_strct *philo)
{
	static int	i;
	static int	ret;
	sem_t		*semfork;
	sem_t		*semstate;
	sem_t		*semprint;

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_STATE);
	sem_unlink(SEM_PRINT);
	semfork = sem_open(SEM_FORK, O_CREAT, 0660, philo[0].nbrphilos);
	semstate = sem_open(SEM_STATE, O_CREAT, 0660, 1);
	semprint = sem_open(SEM_PRINT, O_CREAT, 0660, 1);
	while (i < philo[i].nbrphilos)
	{
		philo[i].semfork = semfork;
		philo[i].semstate = semstate;
		philo[i].semprint = semprint;
		i++;
	}
	return (ret);
}
