#include "philo_one.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;

int 	initProc(s_strct **philo, int *lfork, int *rfork, void *arg)
{
	pthread_mutex_lock(&mutex1);
	*philo = (s_strct*)arg;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex1);
	*lfork = (*philo)->fork[0];
	*rfork = (*philo)->fork[1];
	gettimeofday(&(*philo)->start, NULL);
	gettimeofday(&(*philo)->end, NULL);
	pthread_mutex_unlock(&mutex1);
	return (0);
}

void	printMessage(s_strct *philo, int status)
{
	long long int start, now;
	struct timeval nowms, startms;

	gettimeofday(&nowms, NULL);
	start = (philo->stamp->tv_usec / 1000) + (philo->stamp->tv_sec * 1000);
	now = (nowms.tv_usec / 1000) + (nowms.tv_sec * 1000);
	int i = philo->id;
	if (status == EATING)
		philo->queue[i] = (now - start);
	pthread_mutex_lock(&mutex3);
	ft_putstr_fd(ft_itoa((int)now - start), 1);
	ft_putstr_fd(" ", 1);
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
	pthread_mutex_unlock(&mutex3);
}

int	checkTime(s_strct *philo)
{
	//pthread_mutex_lock(&mutex4);
	if (!*philo->isDead)
	{
		gettimeofday(&philo->end, NULL);
		philo->elapsed = (int)((philo->end.tv_usec / 1000) + (philo->end.tv_sec * 1000))\
		       	- ((philo->start.tv_usec / 1000) + (philo->start.tv_sec * 1000));
		//printf("time elapsed is %d\n", philo->elapsed);
		if (philo->elapsed > philo->timeToDie)
		{
			printf("elapsed is %d\n", philo->elapsed);
			fflush(stdout);
			*philo->isDead = 1;
			pthread_mutex_unlock(&mutex1);
			//usleep((philo->timeToEat + philo->timeToSleep) * 1000);
			printMessage(philo, DIED);
			return (-1);
		}
	}
	if (*philo->isDead)
	{
		if (philo->nbrOfEat)
			return (0);
		pthread_mutex_unlock(&mutex1);
		return (-1);
	}
	//pthread_mutex_unlock(&mutex4);
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

void setqueue(s_strct *philo, int status)
{
	int i;

	i = 0;
        if (status == INIT)
        {
                while (i < philo->nbrPhilos)
                        philo->queue[i++] = gettimeofday(philo->stamp, NULL);
        }
		
}

int queue(s_strct *philo)
{
	int i;
	int j;
	int ret;
	
	i = 0;
	j = 0;
	ret = -1;
	
	ret = philo->queue[i];
	while (i < philo->nbrPhilos)
	{
		while (j < philo->nbrPhilos)
		{
			if (philo->queue[j] < ret)
				ret = philo->queue[j];
			j++;
		}
		j = 0;
		i++;
	}
	i = philo->id;
	return ((philo->queue[i] == ret));// || ret == -1);
//	static int n;
//	static int c;
//	int ret;
//
//	ret = 0;
//	if (!n)
//		n++;
//	if (n%2)
//	{
//		if ((philo->id+1)%2)
//		{
//			if (c)
//			{
//				n++;
//				c = 0;
//			}
//			c++;
//			ret = 1;
//		}
//	}
//	else
//	{
//		if (!(philo->id+1)%2)
//		{
//			if (c)
//			{
//				n++;
//				c = 0;
//			}
//			c++;
//			ret = 1;
//		}       
//	}
	//return (ret);
}

int isWaiting(s_strct **philo)
{
	int		lfork;
	int		rfork;
	int		ret;
	static int	odd;

	
	ret = 1;
	lfork = (*philo)->fork[0];
	rfork = (*philo)->fork[1];
	pthread_mutex_lock(&mutex2);
        if (((*philo)->bfork[lfork] == 1 && (*philo)->bfork[rfork] == 1 && queue(*philo)))
	{
		setforks(*philo, TAKEN);
		ret = 0;
	}
	if (*((*philo)->isDead))
		ret = 0;
	pthread_mutex_unlock(&mutex2);
	return (ret);
}

int isSleeping(int sleep)
{
//	struct timeval before, after;
	int i = sleep/200;
	//gettimeofday(&before, NULL);
	while (i--)
		usleep(155);
	//gettimeofday(&after, NULL);
	///int elapsed = (int)((after.tv_usec / 1000) + (after.tv_sec * 1000))\
		       	- ((before.tv_usec / 1000) + (before.tv_sec * 1000));
	//printf("time sleeping is: %d\n", elapsed);
	//fflush(stdout);
	return (0);
}

void	*threadProc(void *arg)
{
	int	lfork;
	int	rfork;
	int	ret = 0;
	s_strct	*philo;

	initProc(&philo, &lfork, &rfork, arg);
	if ((philo->id+1)%2)
		usleep(1000);
	while(1)
	{
		while (isWaiting(&philo))
			if (checkTime(philo))
				return (NULL);
		printMessage(philo, FORK);
		pthread_mutex_lock(&philo->mfork[lfork]);
		pthread_mutex_lock(&philo->mfork[rfork]);
//		if (philo->nbrOfEat > 0)
//			philo->nbrOfEat--;
		printMessage(philo, EATING);
		if (checkTime(philo))
		{
			pthread_mutex_unlock(&philo->mfork[lfork]);
			pthread_mutex_unlock(&philo->mfork[rfork]);
			return (NULL);
		}
		gettimeofday(&philo->start, NULL);
		isSleeping(philo->timeToEat * 1000);
		pthread_mutex_unlock(&philo->mfork[lfork]);
		pthread_mutex_unlock(&philo->mfork[rfork]);
		pthread_mutex_lock(&mutex2);
		setforks(philo, FREE);
		pthread_mutex_unlock(&mutex2);
		printMessage(philo, SLEEPING);
		isSleeping(philo->timeToSleep * 1000);
		if (checkTime(philo))
			return (NULL);
		printMessage(philo, THINKING);
	}
	return (NULL);
}
