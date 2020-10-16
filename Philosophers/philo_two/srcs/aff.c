#include "../includes/philo.h"

char    *text(int i)
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

void    aff(t_philo *philo, int i)
{
    char            *tmp;

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