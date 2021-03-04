/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:45:09 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/03/03 19:34:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_one.h"

static int		ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'\
		|| c == '\r' || c == ' ');
}

int				ft_atoi(char *nptr)
{
	int	moins;
	int	nbr;

	moins = 1;
	nbr = 0;
	if (!nptr)
		return (0);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*(nptr++) == '-')
			moins *= -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
		nbr = (10 * nbr + (*(nptr++) - 48));
	if (nbr > INT_MAX)
		return (0);
	return ((int)(moins * nbr));
}
