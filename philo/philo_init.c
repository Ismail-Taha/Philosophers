/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:26:50 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 17:21:52 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "falasifa.h"

static void	init_group_of_three(t_prog *prog)
{
	prog->philos[0].lfork = &prog->forks[0];
	prog->philos[0].rfork = &prog->forks[1];
	prog->philos[1].lfork = &prog->forks[1];
	prog->philos[1].rfork = &prog->forks[2];
	prog->philos[2].lfork = &prog->forks[2];
	prog->philos[2].rfork = &prog->forks[0];
}

static void	init_group_of_two(t_prog *prog, int start_idx)
{
	int	i;
	int	philo_idx;
	int	other_idx;

	i = 0;
	while (i < 2 && (start_idx + i) < prog->philo_count)
	{
		philo_idx = start_idx + i;
		other_idx = start_idx + ((i + 1) % 2);
		prog->philos[philo_idx].lfork = &prog->forks[philo_idx];
		prog->philos[philo_idx].rfork = &prog->forks[other_idx];
		i++;
	}
}

static void	init_basic_data(t_prog *prog)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = prog->philo_count;
	prog->turn = 0;
	while (i < num_philos)
	{
		prog->philos[i].id = i;
		prog->philos[i].prog = prog;
		prog->philos[i].meals = 0;
		i++;
	}
}

static void	init_groups(t_prog *prog)
{
	int	i;
	int	num_philos;

	num_philos = prog->philo_count;
	if (num_philos % 2 != 0)
	{
		init_group_of_three(prog);
		i = 3;
		while (i < num_philos)
		{
			init_group_of_two(prog, i);
			i += 2;
		}
	}
	else
	{
		i = 0;
		while (i < num_philos)
		{
			init_group_of_two(prog, i);
			i += 2;
		}
	}
}

void	philos_init(t_prog *prog)
{
	init_basic_data(prog);
	init_groups(prog);
}
