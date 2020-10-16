#include "../includes/philo.h"

int    clean_ph(t_base *base)
{
    int         i;
    char        *tmp;

    i = 0;
    tmp = NULL;
    if (base)
    {
        if(base->nb_eat > 0)
            kill(base->pid_b, SIGKILL);
        if (base->philo)
        {
            while (i < base->nb_ph)
            {
                kill(base->philo[i].pid, SIGKILL);
                tmp = ft_name("sim", i);
                sem_unlink(tmp);
                free(tmp);
                tmp = ft_name("t_leat", i);
                sem_unlink(tmp);
                free(tmp);
                tmp = NULL;
                i++;
            }
            free(base->philo);
            base->philo = NULL;
        }
        sem_unlink("sem_frk");
        sem_unlink("sem_disp");
    }
    return (1);
}

int    exit_error(t_base *base, int i)
{
    if (i == 2)
    {
        write(1, "Error : Malloc went wrong\n", 26);
        clean_ph(base);
    }
    else if (i == 3)
    {
        write(1, "Error : Semaphore went wrong\n", 26);
        clean_ph(base);
    }
    return (i);
}