#include "philosophers.h"

static int check_meals_count(t_philo *philo)
{
	int enough_meals = 0;
	if (philo->prog->meals_required != -1)
	{
		pthread_mutex_lock(&philo->meal_mtx);
		if (philo->meals >= philo->prog->meals_required)
			enough_meals = 1;
		pthread_mutex_unlock(&philo->meal_mtx);
	}
	return (enough_meals);
}

static int check_if_all_ate(t_prog *prog)
{
	int i = -1;
	int all_ate = 1;
	if (prog->meals_required == -1)
		return (0);
	while (++i < prog->philo_count)
	{
		if (!check_meals_count(&prog->philos[i]))
		{
			all_ate = 0;
			break ;
		}
	}
	return (all_ate);
}

void *philo_thread(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!get_dead(philo->prog))
	{
		if (eat_action(philo))
			break ;
		if (sleep_think(philo))
			break ;
	}
	return (NULL);
}

void *philo_thread3(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!get_dead(philo->prog))
	{
		if (eat3_action(philo))
			break ;
		if (sleep_think(philo))
			break ;
	}
	return (NULL);
}

void *monitor_thread(void *arg)
{
	t_prog *prog = (t_prog *)arg;
	int i;
	while (!get_dead(prog))
	{
		i = -1;
		while (++i < prog->philo_count)
		{
			if (get_time() - get_last_meal(&prog->philos[i]) >= prog->t_die)
				return (set_dead(prog->philos), print_state(&prog->philos[i], "died"), NULL);
		}
		if (prog->meals_required != -1 && check_if_all_ate(prog))
			return (set_dead(prog->philos), NULL);
		if (!is_critical_time(prog))
			usleep(100);
	}
	return (NULL);
}
