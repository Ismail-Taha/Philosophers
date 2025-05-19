/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:27:01 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 17:21:57 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "falasifa.h"

static void	take_forks(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->rfork;
		*second_fork = philo->lfork;
	}
	else
	{
		*first_fork = philo->lfork;
		*second_fork = philo->rfork;
	}
	pthread_mutex_lock(*first_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(*second_fork);
	print_state(philo, "has taken a fork");
}

int	eat_action(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (get_dead(philo->prog))
		return (1);
	take_forks(philo, &first_fork, &second_fork);
	if (get_dead(philo->prog))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (1);
	}
	print_state(philo, "is eating");
	set_last_meal(philo);
	ft_usleep(philo->prog->t_eat, philo->prog);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (0);
}

int	sleep_think(t_philo *philo)
{
	if (get_dead(philo->prog))
		return (1);
	print_state(philo, "is sleeping");
	ft_usleep(philo->prog->t_sleep, philo->prog);
	if (get_dead(philo->prog))
		return (1);
	print_state(philo, "is thinking");
	return (0);
}
