#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long int		znak;
	long int		result;
	unsigned int	i;

	i = 0;
	znak = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		znak = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)result * znak);
}

unsigned long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000);
}

void	usleep_modified(unsigned long ms)
{
	unsigned long	time;

	time = ft_get_time() + ms;
	while ((ft_get_time() < time))
		usleep(1000);
}

void	ft_free(t_philo *phil, t_tr_philos *tr_phil)
{
	sem_close(phil->sem_f);
	sem_close(phil->sem_p);
	free(phil->pid);
	free(tr_phil);
	free(phil);
}
