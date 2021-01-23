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

int		init_sem(t_philo *philo, int i)
{
	char	*tmp;

	tmp = ft_name("/t_leat", i);
	sem_unlink(tmp);
	philo->t_leat = sem_open(tmp, O_CREAT, 0644, 1);
	free(tmp);
	tmp = NULL;
	tmp = ft_name("/sem", i);
	sem_unlink(tmp);
	philo->sem = sem_open(tmp, O_CREAT, 0644, 1);
	free(tmp);
	tmp = NULL;
	return (0);
}

int		init_philo(t_base *base)
{
	int		i;

	i = -1;
	if (!(base->philo = malloc(sizeof(t_base) * base->nb_ph)))
		return (2);
	while (++i < base->nb_ph)
	{
		base->philo[i].nb = i;
		base->philo[i].ping = 1;
		base->philo[i].tour = 0;
		base->philo[i].base = base;
		init_sem(&base->philo[i], i);
	}
	sem_unlink("/sem_end");
	base->end = sem_open("/sem_end", O_CREAT, 0644, 0);
	sem_unlink("/sem_frk");
	sem_unlink("/sem_text");
	base->frk = sem_open("/sem_frk", O_CREAT, 0644, base->nb_ph);
	base->text = sem_open("/sem_text", O_CREAT, 0644, 1);
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
	else if ((base->t_eat = is_atoi(argv[3])) < 60)
		write(2, "Wrong number: time to eat\n", 26);
	else if ((base->t_sleep = is_atoi(argv[4])) < 20)
		write(2, "Wrong number: time to sleep\n", 28);
	else if (argc == 6 && (base->nb_eat = is_atoi(argv[5])) < 0)
		write(2, "Wrong number of meals\n", 20);
	else
		return (init_philo(base));
	return (1);
}

int		main(int argc, char **argv)
{
	t_base	base;
	int		i;

	g_point = -2;
	g_end = 0;
	memset(&base, 0, sizeof(t_base));
	if ((i = check_arg(argc, argv, &base)))
		return (exit_error(&base, i));
	if ((i = init_process(&base)))
		return (exit_error(&base, 3));
	clean_ph(&base, -1, NULL);
	g_end = 1;
	return (0);
}
