/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:26:53 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 18:51:49 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "falasifa.h"

int	mutexes_init(t_prog *prog)
{
	int	i;

	if (pthread_mutex_init(&prog->print_mtx, NULL)
		|| pthread_mutex_init(&prog->dead_mtx, NULL))
		return (1);
	if (prog->philo_count % 2 != 0)
		pthread_mutex_init(&prog->turn_mtx, NULL);
	i = -1;
	while (++i < prog->philo_count)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL)
			|| pthread_mutex_init(&prog->philos[i].meal_mtx, NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&prog->forks[i]);
				pthread_mutex_destroy(&prog->philos[i].meal_mtx);
			}
			return (pthread_mutex_destroy(&prog->print_mtx),
				pthread_mutex_destroy(&prog->dead_mtx),
				1);
		}
	}
	return (0);
}

static int	create_threads(t_prog *prog)
{
	int	i;

	i = 0;
	prog->start = get_time();
	while (i < prog->philo_count)
	{
		pthread_mutex_lock(&prog->philos[i].meal_mtx);
		prog->philos[i].last_meal_time = get_time();
		pthread_mutex_unlock(&prog->philos[i].meal_mtx);
		if (prog->philo_count % 2 != 0 && i < 3)
		{
			if (pthread_create(&prog->threads[i], NULL, philo_thread3,
					&prog->philos[i]))
				return (1);
		}
		else
		{
			if (pthread_create(&prog->threads[i], NULL, philo_thread,
					&prog->philos[i]))
				return (1);
		}
		i++;
	}
	pthread_create(prog->monitor, NULL, djikstra_mon, prog);
	return (0);
}

int	prog_init(t_prog *prog)
{
	prog->dead = 0;
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->philo_count);
	prog->threads = malloc(sizeof(pthread_t) * prog->philo_count);
	prog->monitor = malloc(sizeof(pthread_t));
	prog->philos = malloc(sizeof(t_philo) * prog->philo_count);
	if (!prog->forks || !prog->threads || !prog->philos)
	{
		if (prog->forks)
			free(prog->forks);
		if (prog->threads)
			free(prog->threads);
		if (prog->philos)
			free(prog->philos);
		return (1);
	}
	if (prog->philo_count % 2 != 0)
		prog->turn = 0;
	if (mutexes_init(prog))
		return (free(prog->forks), free(prog->threads), free(prog->philos), 1);
	return (philos_init(prog), create_threads(prog));
}

void	prog_clean(t_prog *prog)
{
	int	i;

	if (prog->monitor)
		pthread_join(*prog->monitor, NULL);
	if (prog->threads)
	{
		i = -1;
		while (++i < prog->philo_count)
			pthread_join(prog->threads[i], NULL);
		i = -1;
		while (++i < prog->philo_count)
		{
			pthread_mutex_destroy(&prog->forks[i]);
			pthread_mutex_destroy(&prog->philos[i].meal_mtx);
		}
		pthread_mutex_destroy(&prog->print_mtx);
		pthread_mutex_destroy(&prog->dead_mtx);
		if (prog->philo_count % 2 != 0)
			pthread_mutex_destroy(&prog->turn_mtx);
		free(prog->forks);
		free(prog->threads);
		free(prog->philos),
		free(prog->monitor);
	}
}
