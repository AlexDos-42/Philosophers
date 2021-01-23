/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:08:23 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 19:53:28 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void		clean_ph(t_base *base, int i, char *tmp)
{
	if (!base)
		return ;
	if (base->philo)
	{
		while (++i < base->nb_ph)
		{
			kill(base->philo[i].pid, SIGKILL);
			tmp = ft_name("/sem", i);
			sem_close(base->philo[i].sem);
			sem_unlink(tmp);
			free(tmp);
			tmp = ft_name("/t_leat", i);
			sem_close(base->philo[i].t_leat);
			sem_unlink(tmp);
			free(tmp);
		}
		free(base->philo);
		base->philo = NULL;
	}
	sem_close(base->frk);
	sem_close(base->text);
	sem_destroy(base->frk);
	sem_destroy(base->text);
	sem_unlink("/sem_frk");
	sem_unlink("/sem_text");
}

int			exit_error(t_base *base, int i)
{
	if (i == 2)
	{
		write(2, "Error : Malloc went wrong\n", 26);
		clean_ph(base, -1, NULL);
	}
	else if (i == 3)
	{
		write(2, "Error : Semaphore went wrong\n", 26);
		clean_ph(base, -1, NULL);
	}
	return (i);
}
