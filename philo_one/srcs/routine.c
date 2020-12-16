/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:20:25 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/16 18:49:34 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void		ft_frk(t_philo *philo)
{
	pthread_mutex_lock(&philo->base->fork[philo->frk_l]);
	aff(philo, 1);
	pthread_mutex_lock(&philo->base->fork[philo->frk_r]);
	aff(philo, 1);
}

void		ft_frk_no(t_philo *philo)
{
	pthread_mutex_unlock(&philo->base->fork[philo->frk_l]);
	pthread_mutex_unlock(&philo->base->fork[philo->frk_r]);
}

void		eat(t_philo *philo)
{
	aff(philo, 2);
	philo->der = chronos();
	pthread_mutex_lock(&philo->t_leat);
	usleep(philo->base->t_eat * 1000);
	philo->tour++;
	pthread_mutex_unlock(&philo->t_leat);
}

void		sleeping(t_philo *philo)
{
	aff(philo, 3);
	usleep(philo->base->t_sleep * 1000);
}
