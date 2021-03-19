#include "philo_two.h"

int checkerror(char **input)
{
        int i;

        i = 1;
        while(input[i] && ft_atoi(input[i]) >= 0)
                i++;
        return ((i >= 4) && (i <= 5));
}

int	threadJoin(int nOfThreads, pthread_t *thread, void **ret)
{
	static int i;

	while (i < nOfThreads)
		pthread_join(thread[i++], ret);
	return (0);
}

int	threadCreate(int nOfThreads, pthread_t *thread, s_strct *arg)
{
	static int	i;

	while (i < nOfThreads)
	{
		pthread_create(&thread[i], NULL, threadProc, (void*)&arg[i]);
		i++;
	}
	return (0);
}

int	initiateThread(s_strct *philo, int nbrPhilos)
{
	pthread_t	thread[nbrPhilos];	

	threadCreate(nbrPhilos, &thread[0], philo);
	threadJoin(nbrPhilos, &thread[0], NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	s_strct	*philo;

	if (!checkerror(argv))
		return (0);
	initiateThread(init(argv, &philo[0]), ft_atoi(argv[1]));
	return (0);
}
