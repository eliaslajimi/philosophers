/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:36:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	printerror(int ret)
{
	if (ret == EAGAIN)
		ft_putstr_fd("insufficient ressources to\
		create thread\n", 1);
	if (ret == EINVAL)
		ft_putstr_fd("invalid settings in attribut\
		during thread initialization\n", 1);
	if (ret == EPERM)
		ft_putstr_fd("No permission to set scheduling\
		policy specified by attribute during thread initialization\n", 1);
	else
		ft_putstr_fd("Unknown problem has happened\n", 1);
}

int		checkerror(char **input)
{
	int i;

	i = 1;
	while (input[i] && ft_atoi(input[i]) >= 0)
		i++;
	return ((i < 5) || (i > 6));
}

void	freestruct(t_strct *philo)
{
	free(philo->isdead);
	free(philo->stamp);
	free(philo->bfork);
	free(philo->queue);
	free(philo);
}

int		setsem(t_strct *philo)
{
	static int	i;
	int		nbrphilos;
	sem_t		*semfork;
	sem_t		*semthread;
	sem_t		*semprint;

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_THREAD);
	semfork = malloc(sizeof(sem_t));
	semthread = malloc(sizeof(sem_t));
	semprint = malloc(sizeof(sem_t));
	semthread = sem_open(SEM_FORK, O_CREAT, 0660, nbrphilos);
	semprint = sem_open(SEM_PRINT, O_CREAT, 0660, 1);
	semthread = sem_open(SEM_THREAD, O_CREAT, 0660, 1);
	while (i < philo[0].nbrphilos)
	{
		philo[i].semfork = semfork;
		philo[i].semprint = semprint;
		philo[i].semthread = semthread;
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int			*isdead;
	static int	i;
	static int	ret;
	t_strct		*philo;

	isdead = malloc(4);
	*isdead = 0;
	if (checkerror(argv))
		return (0);
	philo = init(argv, philo, i, isdead);
	setsem(philo);
	ret = initiatethread(philo, ft_atoi(argv[1]));
	if (ret)
		printerror(ret);
	return (ret);
}
