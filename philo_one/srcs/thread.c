/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:21:20 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/16 18:47:16 by alesanto         ###   ########.fr       */
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
		pthread_mutex_lock(&philo->t_leat);
		if (!philo->base->finish && chronos() - philo->der > philo->base->t_die)
		{
			aff(philo, 5);
			pthread_mutex_unlock(&philo->t_leat);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->t_leat);
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
		eat(philo);
		ft_frk_no(philo);
		if (philo->base->nb_eat > 0 && check_philo(philo))
			return (NULL);
		sleeping(philo);
		aff(philo, 4);
	}
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
		if (pthread_create(&base->philo[i].thread, NULL,
			&is_he_dead, (void*)&base->philo[i]))
			return (1);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < base->nb_ph)
		pthread_join(base->philo[i++].thread, NULL);
	return (0);
}
