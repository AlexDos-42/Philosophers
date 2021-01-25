/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:12:19 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 18:58:21 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*is_he_dead(void *args)
{
	t_philo *philo;

	philo = (t_philo*)args;
	while (philo->ping)
	{
		if (g_base.stop == 1 && chronos() - philo->der > g_base.t_die)
		{
			philo->ping = 0;
			aff(g_base.philo, 5);
			sem_post(g_base.end);
		}
		usleep(100);
	}
	return (NULL);
}

int		start_routine(t_philo *philo)
{
	pthread_t	thread;
	int			nb_meal;

	nb_meal = 0;
	philo->der = chronos();
	if (pthread_create(&thread, NULL, &is_he_dead, philo))
		return (1);
	pthread_detach(thread);
	while (1)
	{
		ft_frk(philo);
		eat(philo);
		nb_meal++;
		if (nb_meal == g_base.nb_eat)
			sem_post(g_base.sem);
		ft_frk_no();
		sleeping(philo);
		aff(philo, 4);
	}
	return (0);
}

void	*end(void *args)
{
	(void)args;
	sem_wait(g_base.end);
	g_base.stop = 0;
	return (NULL);
}

void	*check_philo(void *args)
{
	int			j;

	j = 0;
	(void)args;
	while (1)
	{
		sem_wait(g_base.sem);
		j++;
		if (j == g_base.nb_ph)
			break ;
	}
	if (g_base.stop == 1)
		aff(g_base.philo, 6);
	g_base.stop = 0;
	return (NULL);
}

int		init_process(void)
{
	int			i;
	pthread_t	thread_end;
	pthread_t	thread_nb;

	i = -1;
	g_base.time = chronos();
	g_base.stop = 1;
	if (pthread_create(&thread_end, NULL, end, NULL))
		return (1);
	if (pthread_create(&thread_nb, NULL, check_philo, NULL))
		return (1);
	pthread_detach(thread_end);
	pthread_detach(thread_nb);
	while (++i < g_base.nb_ph)
	{
		g_base.philo[i].der = chronos();
		if (!(g_base.philo[i].pid = fork()))
			start_routine(&g_base.philo[i]);
		else if (g_base.philo[i].pid < 0)
			return (1);
		usleep(100);
	}
	while (g_base.stop == 1)
		usleep(100);
	return (0);
}
