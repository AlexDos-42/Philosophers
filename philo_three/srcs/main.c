/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:11:20 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 19:11:37 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_base	g_base;

int		is_atoi(char *tab)
{
	int			i;

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

int		init_philo(void)
{
	int		i;

	i = -1;
	if (!(g_base.philo = malloc(sizeof(t_base) * g_base.nb_ph)))
		return (2);
	while (++i < g_base.nb_ph)
	{
		g_base.philo[i].nb = i;
		g_base.philo[i].ping = 1;
		g_base.philo[i].tour = 0;
		g_base.philo[i].base = &g_base;
	}
	sem_unlink("/sem");
	g_base.sem = sem_open("/sem", O_CREAT, 0644, 0);
	sem_unlink("/sem_end");
	g_base.end = sem_open("/sem_end", O_CREAT, 0644, 0);
	sem_unlink("/sem_frk");
	sem_unlink("/sem_text");
	g_base.frk = sem_open("/sem_frk", O_CREAT, 0644, g_base.nb_ph);
	g_base.text = sem_open("/sem_text", O_CREAT, 0644, 1);
	return (0);
}

int		check_arg(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (1);
	}
	if ((g_base.nb_ph = is_atoi(argv[1])) < 2)
		write(2, "Wrong number of philosopher\n", 28);
	else if ((g_base.t_die = is_atoi(argv[2])) < 60)
		write(2, "Wrong number: time to die\n", 26);
	else if ((g_base.t_eat = is_atoi(argv[3])) < 60)
		write(2, "Wrong number: time to eat\n", 26);
	else if ((g_base.t_sleep = is_atoi(argv[4])) < 20)
		write(2, "Wrong number: time to sleep\n", 28);
	else if (argc == 6 && (g_base.nb_eat = is_atoi(argv[5])) < 0)
		write(2, "Wrong number of meals\n", 20);
	else
		return (init_philo());
	return (1);
}

int		main(int argc, char **argv)
{
	int		i;

	memset(&g_base, 0, sizeof(t_base));
	if ((i = check_arg(argc, argv)))
		return (exit_error(i));
	if ((i = init_process()))
		return (exit_error(3));
	clean_ph(-1);
	return (0);
}
