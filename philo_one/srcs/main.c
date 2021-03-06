/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:19:40 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/17 16:32:22 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		is_atoi(char *tab)
{
	int		i;

	i = 0;
	while (tab[i] && tab[i] == ' ')
		i++;
	if (tab[i] == '-' || tab[i] == '+')
		i++;
	while (tab[i] && (tab[i] >= '0' && tab[i] <= '9'))
		i++;
	if (tab[i] == '\0')
		return (ft_atoi(tab));
	return (-1);
}

int		init_philo(t_base *base)
{
	int		i;

	i = -1;
	if (!(base->philo = malloc(sizeof(t_base) * base->nb_ph)) ||
	!(base->fork = malloc(sizeof(pthread_mutex_t) * base->nb_ph)))
		return (2);
	while (++i < base->nb_ph)
	{
		base->philo[i].nb = i;
		base->philo[i].tour = 0;
		base->philo[i].frk_l = i;
		base->philo[i].frk_r = (i + 1) % base->nb_ph;
		if (pthread_mutex_init(&base->philo[i].t_leat, NULL))
			return (3);
		base->philo[i].base = base;
		if (pthread_mutex_init(&base->fork[i], NULL))
			return (3);
	}
	if (pthread_mutex_init(&base->text, NULL))
		return (3);
	return (0);
}

int		check_arg(int argc, char **argv, t_base *base)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	if ((base->nb_ph = is_atoi(argv[1])) < 2)
		write(2, "Wrong number of philosopher\n", 28);
	else if ((base->t_die = is_atoi(argv[2])) < 60)
		write(2, "Wrong number: time to die\n", 26);
	else if ((base->t_eat = is_atoi(argv[3])) < 20)
		write(2, "Wrong number: time to eat\n", 26);
	else if ((base->t_sleep = is_atoi(argv[4])) < 60)
		write(2, "Wrong number: time to sleep\n", 28);
	else if (argc == 6 && (base->nb_eat = is_atoi(argv[5])) < 0)
		write(2, "Wrong number of meals\n", 20);
	else
		return (init_philo(base));
	return (1);
}

int		main(int argc, char **argv)
{
	t_base		base;
	int			i;

	memset(&base, 0, sizeof(t_base));
	if ((i = check_arg(argc, argv, &base)))
		return (exit_error(&base, i));
	if ((i = init_thread(&base)))
		return (exit_error(&base, 3));
	clean_ph(&base);
	return (0);
}
