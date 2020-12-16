/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 19:01:28 by alesanto          #+#    #+#             */
/*   Updated: 2020/12/16 19:04:05 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo
{
	int				nb;
	int				tour;
	int				der;
	int				frk_l;
	int				frk_r;
	pthread_t		thread;
	pthread_mutex_t	t_leat;
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
	int				cmb;
	int				finish;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	text;
}					t_base;

/*
** --MAIN--
*/

int					main(int argc, char **argv);

/*
** --TREAD--
*/

int					init_thread(t_base *base);
void				*start_routine(void *args);
void				*is_he_dead(void *args);
int					check_philo(void *args);
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

int					clean_ph(t_base *base);
int					exit_error(t_base *base, int i);

#endif
