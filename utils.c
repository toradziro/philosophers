#include "philo.h"

void	free_philos(t_philo *philos, int32_t num, pthread_mutex_t *forks)
{
	int32_t		i;
	pthread_t	thread;

	i = 0;
	while (i < num)
	{
		thread = *(philos[i].philo);
		pthread_detach(thread);
		pthread_mutex_destroy(&forks[i]);
		++i;
	}
	free(philos->philo);
	free(forks);
	free(philos);
//	while (1) {}
	exit (0);
}

void	check_values(char **argv, int32_t num)
{
	int32_t	i;
	int32_t	j;

	i = 1;
	while (i < num)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				error_handle(WRONG_ARG_VALUE);
			++j;
		}
		++i;
	}
}

int64_t	my_time(void)
{
	struct timeval	tv;
	int64_t			t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t);
}

void	error_handle(int32_t err_id)
{
	if (err_id == MALLOC_ERROR)
		write(STDERR_FILENO, "Error: malloc returned NULL\n", 28);
	else if (err_id == THREAD_ERROR)
		write(STDERR_FILENO, "Error: Thread returned error code\n", 34);
	else if (err_id == MUTEX_ERROR)
		write(STDERR_FILENO, "Error: Mutex returned error code\n", 33);
	else if (err_id == WRONG_ARG_NUM)
		write(STDERR_FILENO, "Error: Invalid amount of arguments\n", 35);
	else if (err_id == WRONG_ARG_VALUE)
		write(STDERR_FILENO, "Error: One of argv have non-integer value, "
			"check it\n", 52);
	exit(err_id);
}

void	report_death(t_table *t, int32_t i)
{
	printf("%lld %d died\n", my_time() - t->ph[i].start_time,
		   t->ph[i].philo_id);
	free_philos(t->ph, t->info->num, t->forks);
}
