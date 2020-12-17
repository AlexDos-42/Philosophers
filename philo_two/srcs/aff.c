/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:49:58 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/17 20:09:44 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*text(int i)
{
	if (i == 1)
		return (" : has taken a fork\n");
	else if (i == 2)
		return (" : is eating\n");
	else if (i == 3)
		return (" : is sleeping\n");
	else if (i == 4)
		return (" : is thinking\n");
	else if (i == 5)
		return (" has died\e[0m\n");
	return ("\e[92m\tLimit of meals reached\n\e[0m");
}

void	aff(t_philo *philo, int i)
{
	char		*tmp;

	sem_wait(philo->base->text);
	if (!philo->base->finish)
	{
		tmp = text(i);
		ft_putnbr_fd(chronos() - philo->base->time, 1);
		if (i == 5)
			write(1, "\e[91m", 5);
		if (i != 6)
		{
			write(1, "\tPhilosopher ", 13);
			ft_putnbr_fd(philo->nb + 1, 1);
		}
		write(1, tmp, ft_strlen(tmp));
		tmp = NULL;
		if (i == 5 || i == 6)
		{
			philo->base->finish = 1;
			return ;
		}
	}
	sem_post(philo->base->text);
}

char	*ft_name(char *str, int j)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * 100);
	while (i < ft_strlen(str))
	{
		tmp[i] = str[i];
		i++;
	}
	while (j > 0)
	{
		tmp[i++] = j % 10 + '0';
		j = j / 10;
	}
	tmp[i] = 0;
	return (tmp);
}
