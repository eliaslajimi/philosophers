#include "philo_two.h"

int	initMutex(s_strct *philo)
{
	int lfork;
	int rfork;

	lfork = philo->fork[0];
	lfork = philo->fork[1];
	return (0);
}

int 	initProc(s_strct **philo, int *lfork, int *rfork, void *arg)
{
	*philo = (s_strct*)arg;
	*lfork = (*philo)->fork[0];
	*rfork = (*philo)->fork[1];
	gettimeofday(&(*philo)->start, NULL);
	gettimeofday(&(*philo)->stamp, NULL);
	return (0);
}

void	printMessage(s_strct *philo, int status)
{
	sem_wait(philo->semPrint);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" ", 1);
	if (status == FORK)
		ft_putstr_fd("has taken a fork\n", 1);
	if (status == EATING)
		ft_putstr_fd("is eating\n", 1);
	if (status == SLEEPING)
		ft_putstr_fd("is sleeping\n", 1);
	if (status == THINKING)
		ft_putstr_fd("is thinking\n", 1);
	if (status == DIED)
		ft_putstr_fd("died\n", 1);
	sem_post(philo->semPrint);
}

int	checkTime(s_strct *philo)
{
	if (!*philo->isDead)
	{
		gettimeofday(&philo->end, NULL);
		philo->elapsed = (int)((philo->end.tv_usec / 1000) + (philo->end.tv_sec * 1000))\
		       	- ((philo->start.tv_usec / 1000) + (philo->start.tv_sec * 1000));
		if (philo->elapsed >= philo->timeToDie)
		{
			*philo->isDead = 1;
			usleep((philo->timeToEat + philo->timeToSleep) * 1000);
			printMessage(philo, DIED);

			return (-1);
		}
	}
	if (*philo->isDead)
	{
		return (-1);
	}
	return (0);
}

int	callFork(s_strct *philo, int status)
{
	int i;
	i = setforks(philo, TAKEN);
	return i;
}

int isWaiting(s_strct **philo)
{
	int	lfork;
	int	rfork;
	int	ret;

	ret = 1;
	lfork = (*philo)->fork[0];
	rfork = (*philo)->fork[1];
        if (((*philo)->bfork[lfork] == 1 && (*philo)->bfork[rfork] == 1))
	{
		setforks(*philo, TAKEN);
		ret = 0;
	}
	if (*((*philo)->isDead))
		ret = 0;
	return (ret);
}

void	*threadProc(void *arg)
{
	int	lfork;
	int	rfork;
	s_strct	*philo;

	initProc(&philo, &lfork, &rfork, arg);
	usleep(philo->id * 10);
	while(1)
	{
		while (isWaiting(&philo))
			if (checkTime(philo))
				return (NULL);
		sem_wait(philo->semFork);
		sem_wait(philo->semFork);
		printMessage(philo, FORK);
		printMessage(philo, EATING);
		gettimeofday(&philo->start, NULL);
		if (checkTime(philo))
		{
			return (NULL);
		}
		usleep(philo->timeToEat * 1000);
		sem_post(philo->semFork);
		sem_post(philo->semFork);
		setforks(philo, FREE);
		printMessage(philo, SLEEPING);
		if (checkTime(philo))
			return (NULL);
		usleep(philo->timeToSleep * 1000);
		printMessage(philo, THINKING);
	}
	return (NULL);
}
