#include "philo.h"

t_philo	*get_life_routine(int ac, char **av)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	ret->nb_ph = ft_atoi(av[1]);
	ret->tm_die = ft_atoi(av[2]);
	ret->tm_eat = ft_atoi(av[3]);
	ret->tm_slp = ft_atoi(av[4]);
	ret->check = 0;
	ret->philo_die = 0;
	pthread_mutex_init(&(ret->wr_eat[0]), NULL);
	pthread_mutex_init(&(ret->wr_eat[1]), NULL);
	if (ac == 6)
	{
		ret->check = 1;
		ret->nb_meal = ft_atoi(av[5]);
	}
	return (ret);
}

int	main(int ac, char **av)
{
	t_philo			*life_routine;
	t_philo_info	**data;

	if (ac == 5 || ac == 6)
	{
		if (check_is_digit(av))
			return (1);
		life_routine = get_life_routine(ac, av);
		data = init_each_philo(life_routine);
		ft_create_threads(data);
		ft_memory_management(life_routine, data);
	}
	else
		ft_putstr_fd(2, "try using 4 or 5 argument\n");
	return (0);
}
