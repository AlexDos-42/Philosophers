/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:08:23 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/18 13:02:20 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void		clean_ph(t_base *base, int i)
{
	char		*tmp;

	tmp = NULL;
	if (!base)
		return ;
	if (base->nb_eat > 0)
		kill(base->pid_b, SIGKILL);
	if (base->philo)
	{
		while (++i < base->nb_ph)
		{
			kill(base->philo[i].pid, SIGKILL);
			tmp = ft_name("sim", i);
			sem_unlink(tmp);
			free(tmp);
			tmp = ft_name("t_leat", i);
			sem_unlink(tmp);
			free(tmp);
			tmp = NULL;
		}
		free(base->philo);
		base->philo = NULL;
	}
	sem_unlink("sem_frk");
	sem_unlink("sem_disp");
}

int			exit_error(t_base *base, int i)
{
	if (i == 2)
	{
		write(2, "Error : Malloc went wrong\n", 26);
		clean_ph(base, -1);
	}
	else if (i == 3)
	{
		write(2, "Error : Semaphore went wrong\n", 26);
		clean_ph(base, -1);
	}
	return (i);
}
