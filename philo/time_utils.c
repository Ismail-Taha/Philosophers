/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:27:19 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 17:21:59 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "falasifa.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long ms, t_prog *prog)
{
	long	start;
	long	sleep_interval;

	start = get_time();
	if (prog->philo_count > 100)
		sleep_interval = 500;
	else if (prog->philo_count > 50)
		sleep_interval = 100;
	else
		sleep_interval = 50;
	while ((get_time() - start) < ms)
	{
		usleep(sleep_interval);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_critical_time(t_prog *prog)
{
	int	ct;

	if (prog->philo_count % 2 == 0)
		ct = (prog->t_die <= prog->t_eat + prog->t_sleep);
	else
		ct = (prog->t_die / 3 <= prog->t_eat + prog->t_sleep);
	return (ct);
}
