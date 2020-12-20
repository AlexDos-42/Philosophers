/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:53:36 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/20 13:21:03 by alesanto         ###   ########.fr       */
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

int		check_philo(void *args)
{
	t_philo			*philo;

	philo = args;
	if (philo->tour >= philo->base->nb_eat)
		philo->base->cmb++;
	if (philo->base->cmb == philo->base->nb_ph)
	{
		aff(philo, 6);
		return (1);
	}
	return (0);
}

void	*is_he_dead(void *args)
{
	t_philo			*philo;

	philo = args;
	while (!philo->base->finish)
	{
		sem_wait(philo->t_leat);
		if (!philo->base->finish && chronos() - philo->der > philo->base->t_die)
		{
			aff(philo, 5);
			sem_post(philo->t_leat);
			return (NULL);
		}
		sem_post(philo->t_leat);
		usleep(100);
	}
	return (NULL);
}

void	*start_routine(void *args)
{
	t_philo			*philo;

	philo = args;
	philo->der = chronos();
	while (!philo->base->finish)
	{
		ft_frk(philo);
		if (philo->base->finish)
			break ;
		eat(philo);
		if (philo->base->finish)
			break ;
		ft_frk_no(philo);
		if (philo->base->nb_eat > 0 && check_philo(philo))
			break ;
		if (philo->base->finish)
			break ;
		sleeping(philo);
		aff(philo, 4);
	}
	sem_post(philo->base->frk);
	sem_post(philo->base->frk);
	sem_post(philo->base->text);
	return (NULL);
}

int		init_thread(t_base *base)
{
	int				i;
	pthread_t		thread;

	i = 0;
	base->time = chronos();
	while (i < base->nb_ph)
	{
		base->philo[i].der = chronos();
		if (pthread_create(&thread, NULL,
			start_routine, (void*)&base->philo[i]))
			return (1);
		pthread_detach(thread);
		if (pthread_create(&base->philo[i].thread,
			NULL, &is_he_dead, (void*)&base->philo[i]))
			return (1);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < base->nb_ph)
		pthread_join(base->philo[i++].thread, NULL);
	return (0);
}
