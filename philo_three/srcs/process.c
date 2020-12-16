/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:12:19 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/16 19:15:27 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		chronos(void)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

void	check_philo(t_base *base)
{
	int			i;
	int			j;

	i = 0;
	while (i < base->nb_eat)
	{
		j = 0;
		while (j < base->nb_ph)
			sem_wait(base->philo[j++].sem);
		i++;
	}
	aff(base->philo, 6);
}

void	*is_he_dead(void *args)
{
	t_philo		*philo;

	philo = args;
	while (philo->ping)
	{
		sem_wait(philo->t_leat);
		if (chronos() - philo->der > philo->base->t_die)
		{
			philo->ping = 0;
			aff(philo, 5);
		}
		sem_post(philo->t_leat);
		usleep(100);
	}
	return (NULL);
}

int		start_routine(t_philo *philo)
{
	pthread_t	thread;

	philo->der = chronos();
	if (pthread_create(&thread, NULL, &is_he_dead, (void*)philo))
		return (1);
	pthread_detach(thread);
	while (1)
	{
		ft_frk(philo);
		eat(philo);
		ft_frk_no(philo);
		sleeping(philo);
		aff(philo, 4);
	}
	return (0);
}

int		init_process(t_base *base)
{
	int			i;

	i = 0;
	base->time = chronos();
	while (i < base->nb_ph)
	{
		base->philo[i].der = chronos();
		if (!(base->philo[i].pid = fork()))
			start_routine(&base->philo[i]);
		else if (base->philo[i].pid < 0)
			return (1);
		usleep(100);
		i++;
	}
	if (base->nb_eat > 0)
	{
		if (!(base->pid_b = fork()))
			check_philo(base);
	}
	waitpid(-1, NULL, 0);
	return (0);
}
