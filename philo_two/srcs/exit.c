/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:50:47 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/20 13:17:50 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		clean_ph(t_base *base)
{
	int		i;

	i = 0;
	if (base)
	{
		if (base->philo)
		{
			while (i < base->nb_ph)
			{
				sem_close(base->philo[i].t_leat);
				sem_unlink(base->philo[i].sem);
				free(base->philo[i].sem);
				base->philo[i].sem = NULL;
				i++;
			}
			free(base->philo);
		}
		sem_close(base->frk);
		sem_close(base->text);
		sem_unlink("frk");
		sem_unlink("text");
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
		write(2, "Error : Semaphore went wrong\n", 26);
		clean_ph(base);
	}
	return (i);
}
