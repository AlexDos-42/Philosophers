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

void		clean_ph(int i)
{
	if (g_base.philo)
	{
		while (++i < g_base.nb_ph)
		{
			kill(g_base.philo[i].pid, SIGKILL);
			sem_post(g_base.sem);
		}
		sem_post(g_base.end);
		free(g_base.philo);
		g_base.philo = NULL;
	}
	sem_close(g_base.end);
	sem_unlink("/end");
	sem_close(g_base.sem);
	sem_unlink("/sem");
	sem_close(g_base.frk);
	sem_close(g_base.text);
	sem_unlink("/sem_frk");
	sem_unlink("/sem_text");
}

int			exit_error(int i)
{
	if (i == 2)
	{
		write(2, "Error : Malloc went wrong\n", 26);
		clean_ph(-1);
	}
	else if (i == 3)
	{
		write(2, "Error : Semaphore went wrong\n", 26);
		clean_ph(-1);
	}
	return (i);
}
