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

int		chronos(void)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

void	*is_he_dead(void *args)
{
	t_philo		*philo;

	philo = args;
	while (philo->ping)
	{
		if (chronos() - philo->der > philo->base->t_die)
		{
			philo->ping = 0;
			aff(philo, 5);
			sem_wait(philo->base->end);
			exit(0);
		}
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
		sem_post(philo->sem);
		ft_frk_no(philo);
		sleeping(philo);
		aff(philo, 4);
	}
	sem_post(philo->t_leat);
	return (0);
}

void	*end(void *base)
{

	sem_wait(((t_base*)base)->end);
	g_end = 0;
	return (NULL);
}

void	*check_philo(void *base)
{
	int			j;

	j = 0;
	while (1)
	{
		sem_wait(((t_base*)base)->philo->sem);
		j++;
		if (j == g_meal * ((t_base*)base)->nb_ph)
			break ;
	}
	aff(((t_base*)base)->philo, 6);
	g_end = 0;
	return (NULL);
}

int		init_process(t_base *base)
{
	int			i;
	pthread_t	thread_end;
	pthread_t	thread_nb;

	i = 0;
	base->time = chronos();
	g_end = 1;
	if (pthread_create(&thread_end, NULL, &end, &base))
		return (1);
	pthread_detach(thread_end);
	if (pthread_create(&thread_nb, NULL, &check_philo, &base))
		return (1);
	pthread_detach(thread_nb);
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
	while(g_end == 1)
	{
		usleep(100);
	}
	i = -1;
	while(++i < base->nb_ph)
	{
		kill(base->philo[i].pid, SIGKILL);
	}
	return (0);
}
