#include "philo_one.h"

/*
 * =================================================
 * Problem: 
 *
 * Program has 5 options:
 * - number_of_philosophers 
 * - time_to_die
 * - time_to_eat
 * - time_to_sleep
 * - number_of_time_each_philosopher_must_eat
 *
 * philosopher should be given a number from 1 to n of phi
 * 5 philosphers are eating, and they all need two forks to eat.
 * Philosopher n can only take fork n and n+1.
 * =================================================
 */

//void *tick(void *data)
//{
//	gettimeofday(&start, NULL);
//	gettimeofday(&end, NULL);
//	int *result;
//	while((end.tvsec - start.tvsec) < time){gettimeofday(&end, NULL); usleep((1000));}
//	if ((end - start) >= time)//address proper calculation
//	{
//		pthread_mutex_unlock(((s_strct*)data)->mutex);
//		return (NULL);
//	}
//	*result = 1;
//	return (result);
//}

void printStruct(s_strct *data)
{
	printf("philo id [%d]\n", data->id);
	fflush(stdout);
	printf("philo id [%d]\n", data->next->id);
	fflush(stdout);
}

//void initfork(int *bfork[])
//{
//	int i;
//
//	i = 0;
//	while (i < size)
//		*bfork[i++] = 1;
//}

int	setforks(s_strct *data, int STATUS)
{

//	printf("%d\n", *bfork[0]);
//	fflush(stdout);
//	printf("goes through %d\n", data->fork[0]);
//	fflush(stdout);
	int i;
	int lfork, rfork;

	lfork = data->fork[0];
	rfork = data->fork[1];
	i = 0;
	if (STATUS == INIT)
	{
		while (i < data->nbrPhilos)
			data->bfork[i++] = 1;
	}
	if (STATUS == FREE)
	{
		data->bfork[lfork] = 1;	
		data->bfork[rfork] = 1;
	}
	if (STATUS == TAKEN)
	{
		data->bfork[lfork] = 0;	
		data->bfork[rfork] = 0;
	}
	i =0;
//	printf("philo %d, lfork: %d, rfork %d\n", data->id, data->bfork[lfork], data->bfork[rfork]);
//	fflush(stdout);
	return ((data->bfork[lfork] == 1 && data->bfork[rfork] == 1));
}

void printtime(s_strct *data)
{
		printf("\n~~~~~~\nphilo %d is eating\n", data->id);
		fflush(stdout);
		//printf("philo %d wait is: %ld micro seconds\n~~~~~~\n", data->id, ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
}

void *startProc(void *strct)
{
	int i = 0;
	s_strct		*data;
	struct timeval start, end;

	printf("goes through here\n");
	fflush(stdout);
	data = (s_strct*)strct;

	//int bfork[data->nbrPhilos];

	setforks(data, INIT);
	//pthread_mutex_t fork[data->nbrPhilos];//put in function
	int lfork = data->fork[0];
	int rfork = data->fork[1];

	pthread_mutex_init(&data->mutex[lfork], NULL);
	pthread_mutex_init(&data->mutex[rfork], NULL);
	gettimeofday(&start, NULL);

	usleep(data->id * 1000);
	while(1)
	{
		while (!setforks(data, NIL))
		{
			gettimeofday(&end, NULL);
			data->elapsed = (end.tv_usec - start.tv_usec) / 1000.0;//ms
			if (data->elapsed >= (data->timeToDie))
			{
				printf("philo %d is dead\n", data->id);
				printf("time starving is %d[%d]\n", data->elapsed , data->timeToDie);
				fflush(stdout);
				exit(1);
			}
			usleep(10);
		}
		setforks(data, TAKEN);	
		pthread_mutex_lock(&data->mutex[lfork]);
		pthread_mutex_lock(&data->mutex[rfork]);
		gettimeofday(&end, NULL);
		printf("\n~~~~~~~\n[philo %d is eating after %d seconds]\n~~~~~~\n\n", data->id,(int) (((end.tv_sec - start.tv_sec))));
		fflush(stdout);
		usleep(data->timeToEat * 1000);
		gettimeofday(&start, NULL);
		pthread_mutex_unlock(&data->mutex[lfork]);
		pthread_mutex_unlock(&data->mutex[rfork]);
		setforks(data, FREE);	
		usleep(data->timeToSleep * 1000);
		printf("[philo %d thinking..]\n", data->id);
		fflush(stdout);
	}
	return NULL;	
}

int checkerror(char **input)
{
	int i;

	i = 1;
	while(input[i] && ft_atoi(input[i]) > 0)
		i++;
	return ((i == 4) || (i == 5));
}

s_strct *init(char **input)//Refactor this function into 2.
{

	int i;
	int nbrPhilos;
	s_strct *philo;
	s_strct *init;

      	nbrPhilos = ft_atoi(input[1]);
	pthread_mutex_t fork[nbrPhilos];//put in function
	int bfork[nbrPhilos];
	i = 0;
	init = malloc(sizeof(s_strct));
	philo = init;
	while(i < nbrPhilos)
	{
		philo->timeToDie	= ft_atoi(input[2]);
		philo->timeToEat	= ft_atoi(input[3]);
		philo->timeToSleep	= ft_atoi(input[4]);
		philo->id		= i;
		philo->nbrPhilos	= nbrPhilos;
		philo->bfork		= &bfork[0];
		philo->mutex		= &fork[0];
		philo->elapsed		= 0;
		if (input[5])
			philo->nbrOfEat	= ft_atoi(input[5]);
		else
			philo->nbrOfEat	= 0;

//==================================== Give fork refactor to function
		if (!philo->id)
			philo->fork[0] = nbrPhilos - 1;
		else
			philo->fork[0] = philo->id - 1;
		philo->fork[1] = philo->id;
//==================================== Give fork refactor to function

		i++;
		philo->next = malloc(sizeof(s_strct));
		philo = philo->next;
	}
	philo = NULL;
	return (init);
}

int wrapper(s_strct *data)//wrapper is a ressource manager
{
 	pthread_t philo[data->nbrPhilos];
	int nbrPhilos = data->nbrPhilos;
	int i = 0;
	while (i < nbrPhilos)
	{
		//usleep(100);
		pthread_create(&philo[i], NULL, startProc, data);
		data = data->next;
		i++;
	}
	i = 0;
	while (i < nbrPhilos)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	s_strct *philo;

	if (!checkerror(argv))
		return (0);
	philo = init(argv);
	wrapper(philo);
	printf("done\n");
	return (0);
}
