#include "philosophers.h"

void set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->meals++;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
}

long get_last_meal(t_philo *philo)
{
	long last_meal_time;

	pthread_mutex_lock(&philo->meal_mtx);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mtx);
	return (last_meal_time);
}

void set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog->dead_mtx);
	philo->prog->dead = 1;
	pthread_mutex_unlock(&philo->prog->dead_mtx);
}

int get_dead(t_prog *prog)
{
	int status;

	pthread_mutex_lock(&prog->dead_mtx);
	status = prog->dead;
	pthread_mutex_unlock(&prog->dead_mtx);
	return (status);
}

void print_state(t_philo *philo, char *state)
{
	long long current_time;

	if (!ft_strncmp(state, "died", 4))
	{
		pthread_mutex_lock(&philo->prog->print_mtx);
		current_time = get_time() - philo->prog->start;
		printf("%lld %d %s\n", current_time, philo->id + 1, state);
		pthread_mutex_unlock(&philo->prog->print_mtx);
		return ;
	}
	if (get_dead(philo->prog))
		return ;
	pthread_mutex_lock(&philo->prog->print_mtx);
	if (!get_dead(philo->prog))
	{
		current_time = get_time() - philo->prog->start;
		printf("%lld %d %s\n", current_time, philo->id + 1, state);
	}
	pthread_mutex_unlock(&philo->prog->print_mtx);
}
