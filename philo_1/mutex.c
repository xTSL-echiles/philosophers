#include "philo.h"

void	ft_mut_fork(t_tr_philos *tr_phil)
{
	pthread_mutex_lock(&tr_phil->phil->mutexes[tr_phil->index]);
	if (tr_phil->phil->dead == 1)
		printf("%ld %d has taken a fork\n", ft_get_time() - \
		tr_phil->phil->time_start, tr_phil->index + 1);
	pthread_mutex_lock(&tr_phil->phil->mutexes[(tr_phil->index + 1) % \
	tr_phil->phil->num_of_phil]);
	pthread_mutex_lock(&tr_phil->phil->m_print);
	if (tr_phil->phil->dead == 1)
		printf("%ld %d has taken a fork\n", ft_get_time() - \
		tr_phil->phil->time_start, tr_phil->index + 1);
	pthread_mutex_unlock(&tr_phil->phil->m_print);
	pthread_mutex_lock(&tr_phil->phil->is_dead[tr_phil->index]);
	 tr_phil->phil->die_start[tr_phil->index] = ft_get_time();
	pthread_mutex_unlock(&tr_phil->phil->is_dead[tr_phil->index]);
	pthread_mutex_lock(&tr_phil->phil->m_print);
	if (tr_phil->phil->dead == 1)
		printf("%ld %d is eatingn\n", ft_get_time() - \
		tr_phil->phil->time_start, tr_phil->index + 1);
	pthread_mutex_unlock(&tr_phil->phil->m_print);
	if (tr_phil->phil->dead == 1)
		usleep_modified(tr_phil->phil->time_to_eat);
	pthread_mutex_unlock(&tr_phil->phil->mutexes[tr_phil->index]);
	pthread_mutex_unlock(&tr_phil->phil->mutexes[(tr_phil->index + 1) % \
	tr_phil->phil->num_of_phil]);
}

void	ft_sleep(t_tr_philos *tr_phil)
{
	pthread_mutex_lock(&tr_phil->phil->m_print);
	if (tr_phil->phil->dead == 1)
		printf("%ld %d is sleeping\n", ft_get_time() - \
		tr_phil->phil->time_start, tr_phil->index + 1);
	pthread_mutex_unlock(&tr_phil->phil->m_print);
	if (tr_phil->phil->dead == 1)
		usleep_modified((tr_phil->phil->time_to_sleep));
	pthread_mutex_lock(&tr_phil->phil->m_print);
	if (tr_phil->phil->dead == 1)
		printf("%ld %d is thinking\n", ft_get_time() - \
		tr_phil->phil->time_start, tr_phil->index + 1);
	pthread_mutex_unlock(&tr_phil->phil->m_print);
}

int	ft_execute(t_philo *phil, t_tr_philos *tr_phil)
{
	phil->count = -1;
	phil->time_start = ft_get_time();
	while (++phil->count < phil->num_of_phil)
	{
		tr_phil[phil->count].index = phil->count;
		if ((pthread_create(&phil->threads[phil->count], NULL, ft_thread_execute, \
		(void *)&tr_phil[phil->count])) != 0)
		{
			printf("Failed pthread create\n");
			return (-1);
		}	
	}
	usleep_modified(phil->time_to_eat / 2 + 100);
	ft_died(phil);
	return (0);
}
