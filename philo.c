#include "philo.h"

void	start_threads(t_philo *philos, t_info *info, pthread_mutex_t *forks)
{
	t_table	*table;
	int32_t	i;
	uint64_t	time;
	pthread_t	monitor;

	i = 0;
	table = (t_table*)calloc(1, sizeof(t_table));
	table->philos = philos;
	table->info = info;
	table->forks = forks;
	time = my_time();
	while (i < info->num)
	{
		philos[i].eat_last_time = time;
		philos[i].start_time = time;
		pthread_create(philos[i].philo, NULL, (void*)start_actions, (void*)
				(&philos[i]));
		++i;
	}
	usleep(1000);
	pthread_create(&monitor, NULL, (void*)check_alive, (void*)table);
	check_alive(table);
}

t_info	*init_info(char **argv)
{
	t_info	*info;

	info = (t_info*)calloc(sizeof(t_info), 1);
	info->num = atoi(argv[1]);
	info->time_die = atoi(argv[2]);
	info->time_eat = atoi(argv[3]);
	info->time_sleep = atoi(argv[4]);
	if (argv[5])
		info->times = atoi(argv[5]);
	else
		info->times = 0;
	return (info);
}

pthread_mutex_t	*init_forks(int32_t nums)
{
	pthread_mutex_t	*forks;
	int32_t	i;

	i = 0;
	forks = (pthread_mutex_t*)calloc(sizeof(pthread_mutex_t), nums);
	while (i < nums)
	{
		pthread_mutex_init(&forks[i], NULL);
		++i;
	}
	return (forks);
}

t_philo	*init_philos(int32_t nums, pthread_mutex_t *forks, t_info *info)
{
	t_philo	*philos;
	int32_t	i;

	i = 0;
	philos = (t_philo*)calloc(sizeof(t_philo), nums);
	while (i < nums)
	{
		philos[i].time_die = info->time_die;
		philos[i].time_sleep = info->time_sleep;
		philos[i].time_eat = info->time_eat;
		philos[i].times = info->times;
		philos[i].philo_id = i;
		philos[i].is_finished = 0;
		philos[i].philo = (pthread_t*)calloc(1, sizeof(pthread_t));
			philos[i].r_fork = &forks[i - 1];
		if (i == 0)
		{
			philos[i].l_fork = &forks[0];
			philos[i].r_fork = &forks[nums - 1];
		}
		else
			philos[i].l_fork = &forks[i];
		++i;
	}
	return (philos);
}

int32_t	main(int32_t argc, char **argv)
{
	t_info	*info;
	t_philo	*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		error_handle(WRONG_ARG_NUM);
	check_values(argv, argc);
	info = init_info(argv);
	forks = init_forks(info->num);
	philos = init_philos(info->num, forks, info);
	start_threads(philos, info, forks);
	return (0);
}