/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:26:57 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 17:21:55 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "falasifa.h"

static int	handle_one_philo(t_prog *prog)
{
	long long	start_time;

	prog->start = get_time();
	start_time = get_time() - prog->start;
	printf("%lld %d %s\n", start_time, 1, "has taken a fork");
	ft_usleep(prog->t_die, prog);
	start_time = get_time() - prog->start;
	printf("%lld %d %s\n", start_time, 1, "is dead");
	return (0);
}

int	main(int ac, char **av)
{
	t_prog	program;

	if (check_args(ac, av))
		return (EXIT_FAILURE);
	if (prog_args_init(&program, ac, av))
		return (EXIT_FAILURE);
	if (program.philo_count == 1)
		return (handle_one_philo(&program));
	if (prog_init(&program))
		return (EXIT_FAILURE);
	prog_clean(&program);
	return (0);
}
