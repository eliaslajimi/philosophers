#include "philo_one.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int	initMutex(s_strct *philo)
{
	int lfork;
	int rfork;

	lfork = philo->fork[0];
	lfork = philo->fork[1];
	//pthread_mutex_init(&(philo->mfork[lfork]), NULL);
	//pthread_mutex_init(&(philo->mfork[rfork]), NULL);
	return (0);
}

int 	initProc(s_strct **philo, int *lfork, int *rfork, void *arg)
{
	pthread_mutex_lock(&mutex1);
	*philo = (s_strct*)arg;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex1);
	*lfork = (*philo)->fork[0];
	*rfork = (*philo)->fork[1];
	gettimeofday(&(*philo)->start, NULL);
	gettimeofday(&(*philo)->stamp, NULL);
	pthread_mutex_unlock(&mutex1);
	return (0);
}

void	printMessage(s_strct *philo, int status)
{
	pthread_mutex_lock(&mutex2);
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
	pthread_mutex_unlock(&mutex2);
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
			printf("%d\n", philo->elapsed);
			fflush(stdout);
			printMessage(philo, DIED);
			pthread_mutex_unlock(&mutex1);
			return (-1);
		}
	}
	if (*philo->isDead)
	{
		pthread_mutex_unlock(&mutex1);
		return (-1);
	}
	return (0);
}

int	callFork(s_strct *philo, int status)
{
	int i;
	pthread_mutex_lock(&mutex1);
	i = setforks(philo, TAKEN);
	pthread_mutex_unlock(&mutex1);
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
	pthread_mutex_lock(&mutex2);
        if (((*philo)->bfork[lfork] == 1 && (*philo)->bfork[rfork] == 1))
	{
		setforks(*philo, TAKEN);
		ret = 0;
	}
	pthread_mutex_unlock(&mutex2);
	if (*((*philo)->isDead))
		ret = 0;
	return (ret);
}

void	*threadProc(void *arg)
{
	int	lfork;
	int	rfork;
	int	ret = 0;
	s_strct	*philo;

	initProc(&philo, &lfork, &rfork, arg);
	usleep(philo->id * 10);
	while(1)
	{
		while (isWaiting(&philo))
			if (checkTime(philo))
				return (NULL);

		printMessage(philo, FORK);
		pthread_mutex_lock(&philo->mfork[lfork]);
		pthread_mutex_lock(&philo->mfork[rfork]);
		printMessage(philo, EATING);
		gettimeofday(&philo->start, NULL);
		if (checkTime(philo))
		{
			pthread_mutex_unlock(&philo->mfork[lfork]);
			pthread_mutex_unlock(&philo->mfork[rfork]);
			return (NULL);
		}

		usleep(philo->timeToEat * 1000);


		pthread_mutex_unlock(&philo->mfork[lfork]);
		pthread_mutex_unlock(&philo->mfork[rfork]);
		pthread_mutex_lock(&mutex2);
		setforks(philo, FREE);
		pthread_mutex_unlock(&mutex2);

		printMessage(philo, SLEEPING);

		if (checkTime(philo))
			return (NULL);

		usleep(philo->timeToSleep * 1000);
		printMessage(philo, THINKING);
	}
	return (NULL);
}
