#include "philo.h"

int	ft_struct_setup_2(t_philo *phil)
{
	phil->count = -1;
	while (++phil->count < phil->num_of_phil)
	{
		if (pthread_mutex_init(&phil->mutexes[phil->count], NULL) != 0)
			return (-1);
	}
	phil->count = -1;
	while (++phil->count < phil->num_of_phil)
	{
		if (pthread_mutex_init(&phil->is_dead[phil->count], NULL) != 0)
			return (-1);
	}
	if (pthread_mutex_init(&phil->m_print, NULL) != 0)
		return (-1);
	return (0);
}

int	ft_struct_setup(t_philo *phil)
{
	phil->mutexes = malloc(sizeof(pthread_mutex_t) * phil->num_of_phil);
	if (phil->mutexes == NULL)
	{
		printf("Malloc 3 mutexes");
		return (-1);
	}
	phil->threads = malloc(sizeof(pthread_t) * phil->num_of_phil + 1);
	if (phil->threads == NULL)
	{
		printf("Malloc 4 threads");
		return (-1);
	}
	phil->is_dead = malloc(sizeof(pthread_mutex_t) * phil->num_of_phil + 1);
	if (phil->is_dead == NULL)
	{
		printf("Malloc 5 threads");
		return (-1);
	}
	phil->dead = 1;
	if (ft_struct_setup_2(phil))
		return (-1);
	return (0);
}

int	ft_struct_phils_setup(t_philo **phil, t_tr_philos *tr_phil)
{
	int	k;

	k = -1;
	while (++k < (*phil)->num_of_phil)
	{
		tr_phil[k].eat_times = (*phil)->all_need_eat;
		tr_phil[k].phil = *phil;
	}
	return (0);
}

void	ft_free_thread(t_philo *phil)
{
	int	i;

	i = -1;
	while (++i < phil->num_of_phil)
	{
		pthread_detach(phil->threads[i]);
		pthread_mutex_destroy(&phil->mutexes[i]);
		pthread_mutex_destroy(&phil->is_dead[i]);
	}
}

void	ft_died(t_philo *phil)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < phil->num_of_phil)
		{
			usleep(50);
			if (!phil->all_need_eat)
				return (ft_free_thread(phil));
			pthread_mutex_lock(&phil->is_dead[i]);
			if ((int)(ft_get_time() - phil->die_start[i]) > phil->time_to_die)
			{
				pthread_mutex_lock(&phil->m_print);
				phil->dead++;
				if (phil->dead > 1)
					printf("%ld %d died\n", ft_get_time() - \
					phil->time_start, i + 1);
				phil->dead = -100000000;
				return (ft_free_thread(phil));
			}
			pthread_mutex_unlock(&phil->is_dead[i]);
		}
	}
}
