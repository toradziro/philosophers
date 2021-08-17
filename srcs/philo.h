#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <sys/time.h>
# include <stdint.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define MALLOC_ERROR -1
# define THREAD_ERROR -2
# define MUTEX_ERROR -3
# define WRONG_ARG_NUM -4
# define WRONG_ARG_VALUE -5

typedef struct s_philo {
	pthread_t		*philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	uint64_t		eat_last_time;
	uint64_t		start_time;
	int32_t			philo_id;
	int32_t			time_die;
	int32_t			time_eat;
	int32_t			time_sleep;
	int32_t			times;
	uint32_t		already_eat;
	int8_t			is_finished;
}				t_philo;

typedef struct s_info {
	int32_t	num;
	int32_t	time_die;
	int32_t	time_eat;
	int32_t	time_sleep;
	int32_t	times;
}				t_info;

typedef struct s_table {
	struct s_info	*info;
	struct s_philo	*ph;
	pthread_mutex_t	*forks;
	int32_t			total_count;
	int32_t			i;
}				t_table;

void			start_actions(void *philo);
void			free_philos(t_philo *philos, int32_t num,
					pthread_mutex_t *forks);
t_info			*init_info(char **argv);
pthread_mutex_t	*init_forks(int32_t nums);
t_philo			*init_philos(int32_t nums, pthread_mutex_t *forks,
					   t_info *info);
void			error_handle(int32_t err_id);
void			check_values(char **argv, int32_t num);
int64_t			my_time(void);
void			take_forks(t_philo *philo);
void			p_eat(t_philo *philo);
void			p_sleep(t_philo *philo);
void			start_threads(t_philo *philos, t_info *info,
					 pthread_mutex_t *forks);
void			check_alive(void *info);
void			report_death(t_table *t, int32_t i);

#endif
