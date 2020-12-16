/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:52:29 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/16 18:55:34 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int		ft_atoi(const char *str)
{
	int			i;
	int			negative;
	int			res;

	i = 0;
	negative = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			negative *= -1;
	while ((ft_isdigit(str[i])) && str[i] != '\0')
		res = res * 10 + (str[i++] - '0');
	return (res * negative);
}

void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long		nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + 48, fd);
	}
	if (nb <= 9)
		ft_putchar_fd((nb % 10) + 48, fd);
}

int		ft_strlen(const char *s)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
