/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:07:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 18:56:20 by alesanto         ###   ########.fr       */
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
	char			*tmp;

	sem_wait(g_base.text);
	if (g_point != -1)
	{
		tmp = text(i);
		ft_putnbr_fd(chronos() - g_base.time, 1);
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
			g_point = -1;
			return ;
		}
	}
	sem_post(g_base.text);
}

char	*ft_name(char *str, int j)
{
	int				i;
	char			*tmp;

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

int		chronos(void)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}
