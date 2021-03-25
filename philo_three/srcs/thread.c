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
			isliving(&philo[i]);
		i++;
	}
	return (0);
}

int		givesem2(t_strct *philo, sem_t *semfork,\
		sem_t *semprint, sem_t *semdead)
{
	philo->semfork = semfork;
	philo->semprint = semprint;
	philo->semdead = semdead;
	gettimeofday(&philo->start, NULL);
	return (0);
}

int		givesem(t_strct *philo)
{
	static int	i;
	sem_t		*semfork;
	sem_t		*semprint;
	sem_t		*semeat;
	sem_t		*semdead;

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_STATE);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_EAT);
	semfork = sem_open(SEM_FORK, O_CREAT, 0660, philo[0].nbrphilos);
	semprint = sem_open(SEM_PRINT, O_CREAT, 0660, 1);
	semdead = sem_open(SEM_DEAD, O_CREAT, 0660, 1);
	semeat = sem_open(SEM_EAT, O_CREAT, 0660, 1);
	while (i < philo[0].nbrphilos)
	{
		givesem2(&philo[i], semfork, semprint, semdead);
		philo[i].semeat = semeat;
		gettimeofday(&philo[i].start, NULL);
		i++;
	}
	sem_wait(philo->semdead);
	sem_wait(philo->semeat);
	return (0);
}
