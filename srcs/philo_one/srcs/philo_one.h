#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <sys/times.h>

typedef struct t_strct
{
	int		nbrPhilos;
	int		timeToDie;	
	int		timeToEat;
	int		timeToSleep;
	pthread_t	thread;	
}	s_strct;

//UTILS
int		ft_atoi(char *nptr);
