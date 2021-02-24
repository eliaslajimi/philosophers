#include "philo_three.h"


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
	int		nbrPhilos;
	sem_t		*semFork;
	sem_t		*semPrint;

	i = 0;
	bfork = malloc(ft_atoi(input[1]) * 4);
	isDead = malloc(4);
	*isDead = 0;
	nbrPhilos = ft_atoi(input[1]);
	philo = malloc(sizeof(s_strct) * (nbrPhilos + 1));
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	semFork = sem_open(SEM_FORKS, O_CREAT, 0660, nbrPhilos);
	semPrint = sem_open(SEM_PRINT, O_CREAT, 0660, 1);
	while (i < nbrPhilos)	
	{
		philo[i].id = i;
		philo[i].nbrPhilos = nbrPhilos;
		philo[i].timeToDie = ft_atoi(input[2]);
		philo[i].timeToEat = ft_atoi(input[3]);
		philo[i].timeToSleep = ft_atoi(input[4]);
		philo[i].nbrOfEat = ft_atoi(input[5]);
		philo[i].isDead = isDead;
		philo[i].semFork = semFork;
		philo[i].semPrint = semPrint;
		distributeForks(&philo[i], &bfork[0]);
		i++;
	}
	setforks(&philo[0], INIT);
	return (&philo[0]);
}
