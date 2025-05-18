#include "philo.h"

/* ft_putstr_fd:
*	Writes a string to the specified file descriptor.
*	If the string is NULL or the file descriptor is invalid, the function does nothing.
*	Used for error messages or general output.
*/
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

/* ft_atoi:
*	Converts a string to an integer.
*	Handles optional leading whitespace and '+'/'-' signs.
*	Returns the integer representation of the string.
*/
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

/* ft_atoi_long:
*	Converts a string to a long long integer.
*	Handles optional leading whitespace and '+'/'-' signs.
*	Returns the long long integer representation of the string.
*/
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

/* ft_error:
*	Prints an error message based on the provided flag.
*	Flag 1: Negative value error.
*	Flag 2: Invalid number format error.
*	Flag 3: Invalid argument error.
*	Returns 1 to indicate an error occurred.
*/
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

/* check_is_digit:
*	Checks if all arguments are valid positive integers.
*	Returns 0 if all arguments are valid, 1 otherwise.
*	Handles edge cases like negative numbers, non-digit characters, and overflow.
*/
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
