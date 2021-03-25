/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:23:32 by user42            #+#    #+#             */
/*   Updated: 2021/03/16 17:06:05 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_TWO_H
# define _PHILO_TWO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <semaphore.h>
# include <math.h>
# include <fcntl.h>
# include <sys/stat.h>

# define NIL 0
# define INIT 1
# define FREE 2
# define TAKEN 3
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4
# define FORK 5

# define SEM_FORK "/sem_fork"
# define SEM_STATE "/sem_state"
# define SEM_PRINT "/sem_print"
# define SEM_DEAD "/sem_dead"
# define SEM_EAT "/sem_eat"

typedef struct		s_strct
{
	pthread_t		thread;
	pthread_t		checktime;
	pthread_t		wrapper;
	pthread_t		eating;
	int				fork[2];
	int				*bfork;
	sem_t			*semfork;
	sem_t			*semstate;
	sem_t			*semprint;
	sem_t			*semdead;
	sem_t			*semeat;
	int				id;
	int				pid;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				nbrofeat;
	int				nbrphilos;
	int				elapsed;
	int				*isdead;
	int				*queue;
	int				haseaten;
	struct timeval	start;
	struct timeval	end;
	struct timeval	*stamp;
}					t_strct;

char				*ft_itoa(int n);
int					ft_atoi(char *nptr);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strdup(char *s1);
int					setforks(t_strct *philo, int status);
void				setqueue(t_strct *philo, int status);
int					distributeforks(t_strct *philo, int *bfork);
void				freestruct(t_strct *philo);
t_strct				*init(char **input, t_strct *philo, int i, int *isdead);
int					checkerror(char **input);
int					threadjoin(int nofthreads, pthread_t *thread);
int					threadcreate(int nofthreads, pthread_t *thread,\
					t_strct *arg);
int					initiatethread(t_strct *philo, int nbrphilos);
int					main(int argc, char **argv);
int					initsem(t_strct *philo);
int					initproc(t_strct **philo, int *lfork, int *rfork,\
					void *arg);
void				*threadproc(void *arg);
void				printmessage(t_strct *philo, int status);
int					elapsed(struct timeval then, struct timeval now);
void				*checktime(void *arg);
int					iswaiting(t_strct **philo);
int					queue(t_strct *philo);
int					ft_strlen(char *s);
int					dead(t_strct *philo);
int					threaddetach(int nofthreads, pthread_t *thread);
int					givesem(t_strct *philo);
int					forkcreate(t_strct *philo);
int					initiateforks(t_strct *philo, int nbrphilos);
int					waitfork(t_strct *philo);
void					*isliving(void *arg);

#endif
