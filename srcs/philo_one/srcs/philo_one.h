#ifndef _PHILO_H
# define _PHILO_H

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
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4
# define FORK 5

extern pthread_mutex_t mutex1;

typedef struct t_strct
{
        pthread_t       thread;
        int             fork[2];
        int             *bfork;
        pthread_mutex_t *mfork;
        pthread_mutex_t *access;
        int             id;
        int             timeToDie;
        int             timeToEat;
        int             timeToSleep;
        int             nbrOfEat;
        int             nbrPhilos;
        int             elapsed;
        int             *isDead;
	int		*queue;
        struct timeval start, end;
        struct timeval *stamp;
        //struct t_strct        *next;
}       s_strct;

//UTILS
char	*ft_itoa(int n);
int	ft_atoi(char *nptr);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);

//INIT
int     setforks(s_strct *philo, int STATUS);
void	setqueue(s_strct *philo, int status);
int	distributeForks(s_strct *philo, int *bfork, pthread_mutex_t *mfork);
s_strct *init(char **input, s_strct *philo);

//MAIN
int	checkerror(char **input);
int	threadJoin(int nOfThreads, pthread_t *thread);
int	threadCreate(int nOfThreads, pthread_t *thread, s_strct *arg);
int	initiateThread(s_strct *philo, int nbrPhilos);
int	main(int argc, char **argv);

//THREAD
int	initMutex(s_strct *philo);
int	initProc(s_strct **philo, int *lfork, int *rfork, void *arg);
void	*threadProc(void *arg);
#endif
