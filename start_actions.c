#include "philo.h"

void	check_alive(void *info)
{
	t_table	*table;
	int32_t i;

	table = (t_table*)info;
	while (1)
	{
		i = 0;
		while (i < table->info->num)
		{
			if (my_time() - table->philos[i].eat_last_time >
				table->philos[i].time_die)
			{
				printf("%lld %d died\n", my_time() - table->philos[i].start_time,
		   				table->philos[i].philo_id);
				free_philos(table->philos, table->info->num, table->forks);
			}
			if (table->philos[i].is_finished == 1)
			{
				table->philos[i].is_finished = 0;
				++table->total_count;
				if (table->total_count >= table->info->num)
					free_philos(table->philos, table->info->num, table->forks);
			}
			++i;
		}
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		printf("%lld %d has taken a fork\n", my_time() - philo->start_time,
		 		philo->philo_id);
		pthread_mutex_lock(philo->l_fork);
		printf("%lld %d has taken a fork\n", my_time() - philo->start_time,
		 		philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%lld %d has taken a fork\n", my_time() - philo->start_time,
			   philo->philo_id);
		pthread_mutex_lock(philo->r_fork);
		printf("%lld %d has taken a fork\n", my_time() - philo->start_time,
			   philo->philo_id);
	}
}

void	p_eat(t_philo *philo)
{
	int64_t	time_start;

	time_start = my_time();
	printf("%lld %d is eating\n", time_start - philo->start_time,
		   philo->philo_id);
	while (my_time() - time_start < philo->time_eat)
	{
	}
	philo->eat_last_time = my_time();
}

void	p_sleep(t_philo *philo)
{
	int64_t	time_start;

	time_start = my_time();
	printf("%lld %d is sleeping\n", time_start - philo->start_time,
		   philo->philo_id);
	while (my_time() - time_start < philo->time_sleep)
	{
	}
}

void	start_actions(void *philo)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo*)philo;
	while (1)
	{
		if (my_time() - curr_philo->eat_last_time > curr_philo->time_die)
			break ;
		if (curr_philo->times && curr_philo->already_eat == curr_philo->times)
			curr_philo->is_finished = 1;
		take_forks(curr_philo);
		curr_philo->eat_last_time = my_time();
		p_eat(curr_philo);
		pthread_mutex_unlock(curr_philo->l_fork);
		pthread_mutex_unlock(curr_philo->r_fork);
		p_sleep(curr_philo);
		printf("%lld %d is thinking\n", my_time() - curr_philo->start_time,
			   curr_philo->philo_id);
		++curr_philo->already_eat;
	}
}