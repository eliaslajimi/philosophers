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

#include "philo_two.h"

int		initiatethread(t_strct *philo, int nbrphilos)
{
	static int	ret;
	pthread_t	timer;
	pthread_t	thread[nbrphilos];

	threaddetach(nbrphilos, &thread[0]);
	threadcreate(nbrphilos, &thread[0], philo);
	ret = pthread_create(&timer, NULL, checktime, (void*)philo);
	threadjoin(nbrphilos, &thread[0]);
	freestruct(philo);
	return (ret);
}

int		threadjoin(int nofthreads, pthread_t *thread)
{
	static int i;

	while (i < nofthreads)
		if (pthread_join(thread[i++], NULL))
			return (-1);
	return (0);
}

int		threaddetach(int nofthreads, pthread_t *thread)
{
	static int i;

	while (i < nofthreads)
		pthread_detach(thread[i++]);
	return (0);
}

int		threadcreate(int nofthreads, pthread_t *thread, t_strct *arg)
{
	static int	i;
	static int	ret;
	sem_t		*semfork;
	sem_t		*semstate;
	sem_t		*semprint;

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_STATE);
	sem_unlink(SEM_PRINT);
	semfork = sem_open(SEM_FORK, O_CREAT, 0660, nofthreads);
	semstate = sem_open(SEM_STATE, O_CREAT, 0660, 1);
	semprint = sem_open(SEM_PRINT, O_CREAT, 0660, 1);
	while (i < nofthreads)
	{
		usleep(50);
		arg[i].semfork = semfork;
		arg[i].semstate = semstate;
		arg[i].semprint = semprint;
		if ((ret = pthread_create(&thread[i], NULL,\
		threadproc, (void*)&arg[i])))
			return (ret);
		i++;
	}
	return (ret);
}
