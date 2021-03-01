#include "philo_one.h"


int     setforks(s_strct *philo, int STATUS)
{
        int i;
        int lfork;
	int rfork;

        lfork = philo->fork[0];
        rfork = philo->fork[1];
        i = 0;
        if (STATUS == INIT)
        {
                while (i < philo->nbrPhilos)
                        philo->bfork[i++] = 1;
        }
        if (STATUS == FREE)
        {
                philo->bfork[lfork] = 1;
                philo->bfork[rfork] = 1;
        }
        if (STATUS == TAKEN)
        {
                philo->bfork[lfork] = 0;
                philo->bfork[rfork] = 0;
        }
        return ((philo->bfork[lfork] == 1 && philo->bfork[rfork] == 1));
}

int	distributeForks(s_strct *philo, int *bfork)
{
	if (!philo->id)
		philo->fork[0] = philo->nbrPhilos - 1;
	else 
		philo->fork[0] = philo->id - 1;
	philo->fork[1] = philo->id;
	philo->bfork = &bfork[0];
	return (0);	
}

s_strct *init(char **input, s_strct *philo)
{
	int		i;
	int		*bfork;
	int		*isDead;
	int		*queue;
	int		nbrPhilos;
	struct timeval	*stamp;
	sem_t		*semFork;
	sem_t		*semPrint;
	sem_t		*semThread;

	i = 0;
	isDead = malloc(4);
	*isDead = 0;
	nbrPhilos = ft_atoi(input[1]);
	bfork = malloc((ft_atoi(input[1]) + 1) * 4);
	stamp = malloc(sizeof(struct timeval));
	queue = malloc((ft_atoi(input[1])) * 4);
	philo = malloc(sizeof(s_strct) * (nbrPhilos + 1));
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_THREAD);
	semFork = sem_open(SEM_FORKS, O_CREAT, 0660, nbrPhilos);
	semPrint = sem_open(SEM_PRINT, O_CREAT, 0660, 1);
	semThread = sem_open(SEM_THREAD, O_CREAT, 0660, 1);
	while (i < nbrPhilos)	
	{
		philo[i].id = i;
		philo[i].nbrPhilos = nbrPhilos;
		philo[i].timeToDie = ft_atoi(input[2]);
		philo[i].timeToEat = ft_atoi(input[3]);
		philo[i].timeToSleep = ft_atoi(input[4]);
		philo[i].nbrOfEat = ft_atoi(input[5]);
		philo[i].isDead = isDead;
		philo[i].queue = queue;
		philo[i].stamp = stamp;
		philo[i].semFork = semFork;
		philo[i].semPrint = semPrint;
		philo[i].semThread = semThread;
		distributeForks(&philo[i], &bfork[0]);
		i++;
	}
	gettimeofday(stamp, NULL);
	setforks(&philo[0], INIT);
	setqueue(&philo[0], INIT);
	return (&philo[0]);
}
