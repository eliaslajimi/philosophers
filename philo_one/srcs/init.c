/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:48:48 by user42            #+#    #+#             */
/*   Updated: 2021/03/11 17:01:28 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			setforks(t_strct *philo, int status)
{
	int i;
	int lfork;
	int rfork;

	lfork = philo->fork[0];
	rfork = philo->fork[1];
	i = 0;
	if (status == INIT)
	{
		while (i < philo->nbrphilos)
			philo->bfork[i++] = 1;
	}
	if (status == FREE)
	{
		philo->bfork[lfork] = 1;
		philo->bfork[rfork] = 1;
	}
	if (status == TAKEN)
	{
		philo->bfork[lfork] = 0;
		philo->bfork[rfork] = 0;
	}
	return ((philo->bfork[lfork] == 1 && philo->bfork[rfork] == 1));
}

int			distributeforks(t_strct *philo, int *bfork, pthread_mutex_t *mfork)
{
	if (!philo->id)
		philo->fork[0] = philo->nbrphilos - 1;
	else
		philo->fork[0] = philo->id - 1;
	philo->fork[1] = philo->id;
	philo->bfork = &bfork[0];
	return (0);
}

t_strct		*init1(char **input, t_strct *philo)
{
	int nbrphilos;
	int i;

	i = 0;
	nbrphilos = ft_atoi(input[1]);
	while (i < nbrphilos)
	{
		philo[i].id = i;
		philo[i].haseaten = 0;
		philo[i].nbrphilos = nbrphilos;
		philo[i].timetodie = ft_atoi(input[2]);
		philo[i].timetoeat = ft_atoi(input[3]);
		philo[i].timetosleep = ft_atoi(input[4]);
		if (ft_atoi(input[5]))
			philo[i].nbrofeat = ft_atoi(input[5]);
		else
			philo[i].nbrofeat = -1;
		i++;
	}
	return (&philo[0]);
}

t_strct		*init(char **input, t_strct *philo, int i, int *isdead)
{
	int				*bfork;
	int				*queue;
	struct timeval	*stamp;
	pthread_mutex_t	*mutex2;

	bfork = malloc((ft_atoi(input[1]) + 1) * 4);
	stamp = malloc(sizeof(struct timeval));
	queue = malloc((ft_atoi(input[1])) * 4);
	mutex2 = malloc((ft_atoi(input[1]) + 1) * sizeof(pthread_mutex_t));
	philo = malloc(sizeof(t_strct) * (ft_atoi(input[1]) + 1));
	while (i < ft_atoi(input[1]))
	{
		init1(input, philo);
		philo[i].isdead = isdead;
		philo[i].queue = queue;
		philo[i].mfork = &mutex2[0];
		philo[i].stamp = stamp;
		pthread_mutex_init(&philo[i].mfork[i], NULL);
		distributeforks(&philo[i], &bfork[0], &mutex2[0]);
		i++;
	}
	gettimeofday(stamp, NULL);
	setforks(&philo[0], INIT);
	setqueue(&philo[0], INIT);
	return (&philo[0]);
}
