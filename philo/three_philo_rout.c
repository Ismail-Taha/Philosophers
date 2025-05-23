/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_philo_rout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:27:04 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 18:21:26 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "falasifa.h"

void	take_forks3(t_philo *philo)
{
	if (philo->lfork < philo->rfork)
	{
		pthread_mutex_lock(philo->lfork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->rfork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->lfork);
		print_state(philo, "has taken a fork");
	}
}

static int	wait_for_turn(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->prog->turn_mtx);
		if (philo->prog->turn == philo->id)
			break ;
		pthread_mutex_unlock(&philo->prog->turn_mtx);
		if (get_dead(philo->prog))
			return (1);
	}
	return (0);
}

static int	release_resources_on_death(t_philo *philo)
{
	if (philo->lfork)
		pthread_mutex_unlock(philo->lfork);
	if (philo->rfork)
		pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(&philo->prog->turn_mtx);
	return (1);
}

int	eat3_action(t_philo *philo)
{
	if (get_dead(philo->prog))
		return (1);
	if (wait_for_turn(philo))
		return (1);
	take_forks3(philo);
	if (get_dead(philo->prog))
		return (release_resources_on_death(philo));
	print_state(philo, "is eating");
	set_last_meal(philo);
	ft_usleep(philo->prog->t_eat, philo->prog);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	if (!get_dead(philo->prog))
		philo->prog->turn = (philo->prog->turn + 1) % 3;
	pthread_mutex_unlock(&philo->prog->turn_mtx);
	return (0);
}
