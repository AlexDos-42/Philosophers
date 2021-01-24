/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:12:56 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 19:49:54 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_frk(t_philo *philo)
{
	sem_wait(g_base.frk);
	sem_wait(g_base.frk);
	aff(philo, 1);
	aff(philo, 1);
}

void	ft_frk_no(void)
{
	sem_post(g_base.frk);
	sem_post(g_base.frk);
}

void	eat(t_philo *philo)
{
	philo->der = chronos();
	aff(philo, 2);
	usleep(philo->base->t_eat * 1000);
	philo->tour++;
}

void	sleeping(t_philo *philo)
{
	aff(philo, 3);
	usleep(philo->base->t_sleep * 1000);
}
