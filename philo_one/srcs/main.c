#include "philo_one.h"

void printError(int ret)
{
	if (ret == EAGAIN)
		printf("insufficient ressources to create thread\n");
	if (ret == EINVAL)
		printf("invalid settings in attribut during thread initialization\n");
	if (ret == EPERM)
		printf("No permission to set scheduling policy specified by attribute during thread initialization\n");
	else 
		printf("else\n");
}

int checkerror(char **input)
{
        int i;

        i = 1;
        while(input[i] && ft_atoi(input[i]) >= 0)
                i++;
	printf("%d\n", i);
	fflush(stdout);
        return ((i < 5) || (i > 6));
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
		usleep(1000);
		if ((ret = pthread_create(&thread[i], NULL, threadProc, (void*)&arg[i])))
			return (ret);
		i++;
	}
	return (ret);
}

void	freeStruct(s_strct *philo)
{
	free(philo->isDead);
	free(philo->stamp);
	free(philo->mfork);
	free(philo->bfork);
	free(philo->queue);
	free(philo);
}

int	initiateThread(s_strct *philo, int nbrPhilos)
{
	static int	ret;
	pthread_t	thread[nbrPhilos];

	ret = threadCreate(nbrPhilos, &thread[0], philo);
	threadJoin(nbrPhilos, &thread[0]);
	freeStruct(philo);
	return (ret);
}

int	main(int argc, char **argv)
{
	static int	ret;
	s_strct		*philo;

	if (checkerror(argv))
		return (0);
	ret = initiateThread(init(argv, &philo[0]), ft_atoi(argv[1]));
	if (ret)
		printError(ret);
	return (ret);
}
