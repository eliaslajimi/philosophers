#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/time.h>
#include <math.h>

# define NIL 0
# define INIT 1
# define FREE 2
# define TAKEN 3

typedef struct t_strct
{
	pthread_t	thread;	
	int		fork[2];
	int		*bfork;
	pthread_mutex_t *mutex;
	int		id;
	int		timeToDie;	
	int		timeToEat;
	int		timeToSleep;
	int		nbrOfEat;
	int		nbrPhilos;
	int		elapsed;
	int		*isDead;
	struct t_strct	*next;

}	s_strct;

//UTILS
int		ft_atoi(char *nptr);
