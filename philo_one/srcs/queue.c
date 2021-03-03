/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:25:07 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:29:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	setqueue(t_strct *philo, int status)
{
	int i;

	i = 0;
	if (status == INIT)
	{
		while (i < philo->nbrphilos)
			philo->queue[i++] = gettimeofday(philo->stamp, NULL);
	}
}

int		queue(t_strct *philo)
{
	int i;
	int j;
	int ret;

	i = 0;
	j = 0;
	ret = -1;
	ret = philo->queue[i];
	while (i < philo->nbrphilos)
	{
		while (j < philo->nbrphilos)
		{
			if (philo->queue[j] < ret)
				ret = philo->queue[j];
			j++;
		}
		j = 0;
		i++;
	}
	i = philo->id;
	return ((philo->queue[i] == ret));
}
