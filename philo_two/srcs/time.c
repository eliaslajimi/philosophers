/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elajimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:02:28 by elajimi           #+#    #+#             */
/*   Updated: 2021/03/16 17:06:58 by elajimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		elapsed(struct timeval then, struct timeval now)
{
	int elapsed;

	elapsed = ((now.tv_usec / 1000) + (now.tv_sec * 1000)) -\
	((then.tv_usec / 1000) + (then.tv_sec * 1000));
	return (elapsed);
}

void	*checktime(void *arg)
{
	t_strct		*philo;
	static int	i;

	philo = (t_strct*)arg;
	while (1)
	{
		if (philo[i].isdead)
			i++;
		while (i < philo[i].nbrphilos)
		{
			if (philo[i].haseaten)
			{
				philo[i].haseaten = 0;
				gettimeofday(&philo[i].start, NULL);
			}
			if (!*philo[i].isdead)
				if (dead(&philo[i]))
					return (0);
			i++;
		}
		i = 0;
	}
	return (0);
}
