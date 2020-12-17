/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:19:34 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/17 20:04:16 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		clean_ph(t_base *base)
{
	int		i;

	i = 0;
	if (base)
	{
		if (base->fork)
		{
			while (i < base->nb_ph)
				pthread_mutex_destroy(&base->fork[i++]);
			free(base->fork);
		}
		pthread_mutex_destroy(&base->text);
		if (base->philo)
		{
			i = 0;
			while (i < base->nb_ph)
				pthread_mutex_destroy(&base->philo[i++].t_leat);
			free(base->philo);
			base->philo = NULL;
		}
	}
	return (1);
}

int		exit_error(t_base *base, int i)
{
	if (i == 2)
	{
		write(2, "Error : Malloc went wrong\n", 26);
		clean_ph(base);
	}
	else if (i == 3)
	{
		write(2, "Error : Mutex went wrong\n", 26);
		clean_ph(base);
	}
	return (i);
}
