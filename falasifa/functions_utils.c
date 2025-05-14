#include "philo.h"

void	ft_putstr_fd(int fd, char *str)
{
	if (!str || fd == -1)
		return ;
	while (*str)
	{
		write (fd, str, 1);
		str++;
	}
}

int	ft_atoi(const char *str)
{
	long long		res;
	int				sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - 48;
		str++;
	}
	return ((int)res * sign);
}

long long	ft_atoi_long(const char *str)
{
	long long		res;
	int				sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - 48;
		str++;
	}
	return (res * sign);
}

int	ft_error(int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd(2, "you should not give an nigative\
value.\ntry with an valid argument");
		return (1);
	}
	if (flag == 2)
	{
		ft_putstr_fd(2, "This number is anvalid number EX: 4 410 200 200..\n");
		return (1);
	}
	if (flag == 3)
	{
		ft_putstr_fd(2, "Anvalid argument EX: 4 410 200 200..\n");
		return (1);
	}
	return (0);
}

int	check_is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+' || av[i][j] == '-')
		{
			if (av[i][j] == '-')
				return (ft_error(1));
			j++;
		}
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (ft_error(2));
			j++;
		}
		if (ft_atoi_long(av[i]) > 2147483647 || (ft_atoi(av[1]) == 0))
			return (ft_error(3));
		i++;
	}
	return (0);
}
