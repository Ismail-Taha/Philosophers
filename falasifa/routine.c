#include "philo.h"

void	ft_print_status(t_philo_info *data, char *str)
{
	pthread_mutex_lock(&(data->data_of_philo->wr_eat[0]));
	pthread_mutex_lock(&(data->data_of_philo->wr_eat[1]));
	if (data->data_of_philo->philo_die)
	{
		pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
		pthread_mutex_unlock(&(data->data_of_philo->wr_eat[0]));
		return ;
	}
	pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
	printf("%lld %d %s\n", (get_time_in_ms() - \
			data->date_of_birth), data->id, str);
	pthread_mutex_unlock(&(data->data_of_philo->wr_eat[0]));
}

int	number_meal_check(t_philo_info **data)
{
	int	counter;

	counter = 0;
	while (counter < (*data)->data_of_philo->nb_ph && \
		data[counter]->n_diner >= (*data)->data_of_philo->nb_meal)
		counter++;
	if (counter == (*data)->data_of_philo->nb_ph)
	{
		(*data)->data_of_philo->philo_die = 1;
		pthread_mutex_unlock(&((*data)->data_of_philo->wr_eat[1]));
		return (-1);
	}
	return (0);
}

int	time_last_eat_check(t_philo_info **data, int count)
{
	t_philo	*data_philo;

	data_philo = (*data)->data_of_philo;
	if (((get_time_in_ms() - data[count]->date_of_birth) - \
	data[count]->last_time_eating) > ((data_philo->tm_die)))
	{
		printf("%lld %d is died\n", (get_time_in_ms() - \
		data[count]->date_of_birth), data[count]->id);
		data_philo->philo_die = 1;
		pthread_mutex_unlock(&(data_philo->wr_eat[1]));
		return (-1);
	}
	return (0);
}

void	*shinigami(void *arg)
{
	t_philo_info	**data;
	t_philo			*data_philo;
	int				count;

	data = (t_philo_info **)arg;
	data_philo = (*data)->data_of_philo;
	while (1)
	{
		count = -1;
		while (++count < data_philo->nb_ph)
		{
			pthread_mutex_lock(&(data_philo->wr_eat[1]));
			if (data_philo->check)
				if (number_meal_check(data) == -1)
					return (NULL);
			if (time_last_eat_check(data, count) == -1)
				return (NULL);
			pthread_mutex_unlock(&(data_philo->wr_eat[1]));
		}
		usleep(100);
	}
}

void	*ft_routine_philo(void *args)
{
	t_philo_info	*data;

	data = (t_philo_info *)args;
	if (!(data->id % 2))
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&(data->data_of_philo->wr_eat[1]));
		if (data->data_of_philo->philo_die)
		{
			pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
			return (NULL);
		}
		pthread_mutex_unlock(&(data->data_of_philo->wr_eat[1]));
		eating(data);
		sleeping(data);
		thinking(data);
	}
}
