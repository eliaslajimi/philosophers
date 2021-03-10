/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:49:34 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:28:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		initiatethread(t_strct *philo, int nbrphilos)
{
	static int	ret;
	pthread_t	thread[nbrphilos];

	ret = threadcreate(nbrphilos, &thread[0], philo);
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


	while (i < nofthreads)
	{
		usleep(10);
		if ((ret = pthread_create(&thread[i], NULL,\
		threadproc, (void*)&arg[i])))
			return (ret);
		i++;
	}
	return (ret);
}
