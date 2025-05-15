#include "philo.h"

/* ft_print_status:
*	Prints the current status of a philosopher (e.g., "is eating", "is thinking").
*	Locks the write mutex to ensure thread-safe output.
*	Skips printing if the simulation has stopped.
*/
void	ft_print_status(t_philosopher *philosopher, char *str)
{
    pthread_mutex_lock(&(philosopher->simulation_data->write_and_meal_mutexes[0]));
    pthread_mutex_lock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
    if (philosopher->simulation_data->simulation_stopped)
    {
        pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
        pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[0]));
        return ;
    }
    pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
    printf("%lld %d %s\n", (get_time_in_ms() - \
            philosopher->simulation_start_time), philosopher->philosopher_id, str);
    pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[0]));
}


/* number_meal_check:
*	Checks if all philosophers have eaten the required number of meals.
*	If all philosophers have eaten enough, sets the simulation stop flag.
*	Returns -1 if the simulation should stop, 0 otherwise.
*/
int	number_meal_check(t_philosopher **data)
{
    int	counter;

    counter = 0;
    while (counter < (*data)->simulation_data->num_philosophers && \
        data[counter]->meals_eaten >= (*data)->simulation_data->num_meals)
        counter++;
    if (counter == (*data)->simulation_data->num_philosophers)
    {
        (*data)->simulation_data->simulation_stopped = 1;
        pthread_mutex_unlock(&((*data)->simulation_data->write_and_meal_mutexes[1]));
        return (-1);
    }
    return (0);
}

/* time_last_eat_check:
*	Checks if a philosopher has exceeded the `time_to_die` without eating.
*	If a philosopher has died, sets the simulation stop flag and prints a death message.
*	Returns -1 if the simulation should stop, 0 otherwise.
*/
int	time_last_eat_check(t_philosopher **data, int count)
{
    t_simulation	*simulation_data;

    simulation_data = (*data)->simulation_data;
    if (((get_time_in_ms() - data[count]->simulation_start_time) - \
    data[count]->last_meal_time) >= ((simulation_data->time_to_die)))
    {
        printf("%lld %d is died\n", (get_time_in_ms() - \
        data[count]->simulation_start_time), data[count]->philosopher_id);
        simulation_data->simulation_stopped = 1;
        pthread_mutex_unlock(&(simulation_data->write_and_meal_mutexes[1]));
        return (-1);
    }
    return (0);
}

/* shinigami:
*	Monitors the philosophers to check for death or if all have eaten enough.
*	Continuously checks the simulation status and stops when necessary.
*	Returns NULL when the simulation ends.
*/
void	*shinigami(void *arg)
{
    t_philosopher	**data;
    t_simulation	*simulation_data;
    int				count;

    data = (t_philosopher **)arg;
    simulation_data = (*data)->simulation_data;
    while (1)
    {
        count = -1;
        while (++count < simulation_data->num_philosophers)
        {
            pthread_mutex_lock(&(simulation_data->write_and_meal_mutexes[1]));
            if (simulation_data->meals_required)
                if (number_meal_check(data) == -1)
                    return (NULL);
            if (time_last_eat_check(data, count) == -1)
                return (NULL);
            pthread_mutex_unlock(&(simulation_data->write_and_meal_mutexes[1]));
        }
        usleep(100);
    }
}

/* ft_routine_philo:
*	The main routine executed by each philosopher thread.
*	Alternates between eating, sleeping, and thinking.
*	Checks the simulation status periodically to exit gracefully.
*/
void	*ft_routine_philosopher(void *args)
{
    t_philosopher	*philosopher;

    philosopher = (t_philosopher *)args;
    if (!(philosopher->philosopher_id % 2))
        usleep(100);
    while (1)
    {
        pthread_mutex_lock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
        if (philosopher->simulation_data->simulation_stopped)
        {
            pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
            return (NULL);
        }
        pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
        eating(philosopher);
        sleeping(philosopher);
        thinking(philosopher);
    }
}
