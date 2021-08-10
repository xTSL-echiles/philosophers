#include "philo.h"

int	ft_argv_set(char **argv, t_philo *phil, int i)
{
	phil->num_of_phil = ft_atoi(argv[1]);
	if (phil->num_of_phil == -1)
		return (-1);
	phil->time_to_die = ft_atoi(argv[2]);
	if (phil->time_to_die == -1)
		return (-1);
	phil->time_to_eat = ft_atoi(argv[3]);
	if (phil->time_to_eat == -1)
		return (-1);
	phil->time_to_sleep = ft_atoi(argv[4]);
	if (phil->time_to_sleep == -1)
		return (-1);
	if (i == 5)
	{
		phil->all_need_eat = ft_atoi(argv[i]);
		if (phil->all_need_eat == -1)
			return (-1);
	}
	return (0);
}

int	ft_pars_argc(char **argv, t_philo *phil)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] != '\0' && !ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (ft_argv_set(argv, phil, i - 1))
		return (1);
	return (0);
}

void	*ft_thread_execute(void *phil0)
{
	t_tr_philos	*tr_phil;

	tr_phil = phil0;
	if (tr_phil->index % 2)
		usleep(tr_phil->phil->time_to_eat / 2);
	tr_phil->phil->die_start[tr_phil->index] = ft_get_time();
	while (tr_phil->phil->dead == 1 && tr_phil->eat_times)
	{
		ft_mut_fork(tr_phil);
		ft_sleep(tr_phil);
		if (tr_phil->eat_times > 0)
		{
			pthread_mutex_lock(&tr_phil->phil->m_print);
			if (tr_phil->index == 0)
				tr_phil->phil->all_need_eat--;
			tr_phil->eat_times--;
			pthread_mutex_unlock(&tr_phil->phil->m_print);
		}
	}
	return (NULL);
}

int	ft_args_setup(t_philo *phil, int argc, char **argv)
{
	phil->all_need_eat = -20;
	if (argc < 5 || argc > 6)
	{
		printf("Main error args\n");
		return (1);
	}
	else
	{
		if (ft_pars_argc(argv, phil))
		{
			printf("Error arguments in main\n");
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*phil;
	t_tr_philos	*tr_phil;

	phil = (t_philo *)malloc(sizeof(t_philo));
	if (phil == NULL)
		return (printf("Malloc main 1"));
	if (ft_args_setup(phil, argc, argv))
		return (-1);
	phil->die_start = (long *)malloc(sizeof(long) * phil->num_of_phil + 1);
	if (phil->die_start == NULL)
		return (printf("Malloc main 2"));
	tr_phil = (t_tr_philos *)malloc(sizeof(t_tr_philos) * phil->num_of_phil);
	if (tr_phil == NULL)
		return (printf("Malloc main 3"));
	if (ft_struct_setup(phil))
		return (-1);
	if (ft_struct_phils_setup(&phil, tr_phil))
		return (-1);
	if (ft_execute(phil, tr_phil))
		return (-1);
	ft_free(phil, tr_phil);
	return (0);
}
