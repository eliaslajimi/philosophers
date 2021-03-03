#include "philo_one.h"

int	initiateThread(s_strct *philo, int nbrPhilos)
{
	static int	ret;
	pthread_t	thread[nbrPhilos];

	ret = threadCreate(nbrPhilos, &thread[0], philo);
	threadJoin(nbrPhilos, &thread[0]);
	freeStruct(philo);
	return (ret);
}


int	threadJoin(int nOfThreads, pthread_t *thread)
{
	static int i;

	while (i < nOfThreads)
		if (pthread_join(thread[i++], NULL))
			return (-1);
	return (0);
}

int	threadDetach(int nOfThreads, pthread_t *thread)
{
	static int i;

	while (i < nOfThreads)
		pthread_detach(thread[i++]);
	return (0);
}

int	threadCreate(int nOfThreads, pthread_t *thread, s_strct *arg)
{
	static int	i;
	static int	ret;

	while (i < nOfThreads)
	{
		usleep(10);
		if ((ret = pthread_create(&thread[i], NULL, threadProc, (void*)&arg[i])))
			return (ret);
		i++;
	}
	return (ret);
}
