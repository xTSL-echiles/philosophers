#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_hilo
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				all_need_eat;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*is_dead;
	pthread_mutex_t	m_print;
	pthread_t		*threads;
	int				count;
	int				dead;
	unsigned long	time_start;
	long			*die_start;
}	t_philo;

typedef struct s_philos
{
	t_philo			*phil;
	int				eat_times;
	int				index;
	unsigned long	die_start;
}				t_tr_philos;

int				ft_isdigit(int c);
unsigned long	ft_get_time(void);
int				ft_atoi(const char *nptr);
int				ft_struct_setup(t_philo *phil);
int				ft_struct_phils_setup(t_philo **phil, t_tr_philos *tr_phil);
int				ft_execute(t_philo *phil, t_tr_philos *tr_phil);
void			*ft_thread_execute(void *phil0);
void			ft_mut_fork(t_tr_philos *tr_phil);
void			ft_sleep(t_tr_philos *tr_phil);
void			usleep_modified(unsigned long time);
void			ft_free(t_philo *phil, t_tr_philos *tr_phil);
void			ft_died(t_philo *phil);
void			ft_free_thread(t_philo *phil);
#endif