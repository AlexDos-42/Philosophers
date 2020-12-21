/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:06:11 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/21 19:05:51 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>

int g_point;
int g_end;

typedef struct		s_philo
{
	int				nb;
	int				tour;
	int				der;
	int				ping;
	char			*tmp;
	sem_t			*t_leat;
	sem_t			*sem;
	pid_t			pid;
	struct s_base	*base;
}					t_philo;

typedef struct		s_base
{
	int				nb_ph;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				nb_eat;
	int				time;
	t_philo			*philo;
	sem_t			*frk;
	sem_t			*text;
	pid_t			pid_b;
}					t_base;

/*
** --MAIN--
*/

int					main(int argc, char **argv);
int					check_arg(int argc, char **argv, t_base *base);
int					init_philo(t_base *base);
int					is_atoi(char *tab);

/*
** --TREAD--
*/

int					init_process(t_base *base);
int					start_routine(t_philo *philo);
void				*is_he_dead(void *args);
void				check_philo(t_base *base);
int					chronos(void);

/*
** --ROUTINE--
*/

void				ft_frk(t_philo *philo);
void				ft_frk_no(t_philo *philo);
void				eat(t_philo *philo);
void				sleeping(t_philo *philo);

/*
** --AFF--
*/

void				aff(t_philo *philo, int i);
char				*text(int i);
char				*ft_name(char *str, int j);

/*
** --OUTILS--
*/

int					ft_atoi(const char *str);
void				ft_putnbr_fd(int n, int fd);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
void				ft_putchar_fd(char c, int fd);

/*
** --EXIT--
*/

void				clean_ph(t_base *base, int i, char *tmp);
int					exit_error(t_base *base, int i);

#endif
