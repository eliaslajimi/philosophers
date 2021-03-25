/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/03/03 19:36:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			init3(t_strct *philo, int *bfork)
{
	distributeforks(philo, &bfork[0]);
	return (0);
}

int			init2(t_strct *philo, int *isdead, int *queue,\
		struct timeval *stamp)
{
	philo->isdead = isdead;
	philo->queue = queue;
	philo->stamp = stamp;
	return (0);
}
