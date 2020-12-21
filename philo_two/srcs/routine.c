/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:52:40 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 19:51:33 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void		ft_frk(t_philo *philo)
{
	sem_wait(philo->base->frk);
	sem_wait(philo->base->frk);
	aff(philo, 1);
	aff(philo, 1);
}

void		ft_frk_no(t_philo *philo)
{
	sem_post(philo->base->frk);
	sem_post(philo->base->frk);
}

void		eat(t_philo *philo)
{
	aff(philo, 2);
	philo->der = chronos();
	sem_wait(philo->t_leat);
	usleep(philo->base->t_eat * 1000);
	philo->tour++;
	sem_post(philo->t_leat);
}

void		sleeping(t_philo *philo)
{
	aff(philo, 3);
	usleep(philo->base->t_sleep * 1000);
}
