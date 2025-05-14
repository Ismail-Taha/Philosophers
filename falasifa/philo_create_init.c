#include "philo.h"

t_philo_info	**init_each_philo(t_philo *life)
{
	int				count;
	t_philo_info	**info;

	count = 0;
	info = malloc(sizeof(t_philo_info *) * life->nb_ph);
	life->forks = malloc(sizeof(pthread_mutex_t) * life->nb_ph);
	while (count < life->nb_ph)
	{
		pthread_mutex_init(&(life->forks[count]), NULL);
		info[count] = malloc(sizeof(t_philo_info));
		count++;
	}
	count = 0;
	while (count < life->nb_ph)
	{
		info[count]->last_time_eating = 0;
		info[count]->data_of_philo = life;
		info[count]->id = count + 1;
		info[count]->right_fork = &(life->forks[count]);
		info[count]->left_fork = &(life->forks[(count + 1) % life->nb_ph]);
		info[count]->n_diner = 0;
		info[count]->date_of_birth = get_time_in_ms();
		count++;
	}
	return (info);
}

void	ft_create_threads(t_philo_info **info)
{
	int			count;
	pthread_t	tid[200];

	count = 0;
	while (count < (*info)->data_of_philo->nb_ph)
	{
		pthread_create(&(tid[count]), NULL, &ft_routine_philo, info[count]);
		count++;
	}
	shinigami(info);
	count = 0;
	while ((*info)->data_of_philo->nb_ph > count)
	{
		pthread_join(tid[count], NULL);
		count++;
	}
}
