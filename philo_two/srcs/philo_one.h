/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:23:32 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:39:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_ONE_H
# define _PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <math.h>
# include <semaphore.h>
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
# define SEM_FORK "/forks"
# define SEM_PRINT "/print"
# define SEM_THREAD "/thread"

typedef struct		s_strct
{
	pthread_t		thread;
	int				fork[2];
	int				*bfork;
	int				id;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				nbrofeat;
	int				nbrphilos;
	int				elapsed;
	int				*isdead;
	int				*queue;
	sem_t				*semfork;
	sem_t				*semprint;
	sem_t				*semthread;
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
int					initmutex(t_strct *philo);
int					initproc(t_strct **philo, int *lfork, int *rfork,\
					void *arg);
void				*threadproc(void *arg);
void				printmessage(t_strct *philo, int status);
int					elapsed(struct timeval then, struct timeval now);
int					checktime(t_strct *philo);
int					iswaiting(t_strct **philo);
int					queue(t_strct *philo);
int					setsem(t_strct *philo);

#endif
