#include "philo.h"

/* dining_of_odd_id:
*	Handles the eating routine for philosophers with odd IDs.
*	Locks the right fork first, then the left fork.
*	Updates the philosopher's last meal time and increments the meal count.
*	Releases the forks after eating.
*/
void	dining_of_odd_id(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->right_fork_mutex);
    ft_print_status(philosopher, "has taken a fork");
    if (philosopher->simulation_data->num_philosophers == 1)
    {
        ft_usleep(philosopher, philosopher->simulation_data->time_to_die + 1);
        pthread_mutex_unlock(philosopher->right_fork_mutex);
        return ;
    }
    pthread_mutex_lock(philosopher->left_fork_mutex);
    ft_print_status(philosopher, "has taken a fork");
    ft_print_status(philosopher, "is eating");
    pthread_mutex_lock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
    philosopher->last_meal_time = (get_time_in_ms() - philosopher->simulation_start_time);
    if (philosopher->simulation_data->meals_required)
        philosopher->meals_eaten++;
    pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
    ft_usleep(philosopher, philosopher->simulation_data->time_to_eat);
    pthread_mutex_unlock(philosopher->right_fork_mutex);
    pthread_mutex_unlock(philosopher->left_fork_mutex);
}

/* dining_of_even_id:
*	Handles the eating routine for philosophers with even IDs.
*	Locks the left fork first, then the right fork.
*	Updates the philosopher's last meal time and increments the meal count.
*	Releases the forks after eating.
*/
void	dining_of_even_id(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->left_fork_mutex);
    ft_print_status(philosopher, "has taken a fork");
    pthread_mutex_lock(philosopher->right_fork_mutex);
    ft_print_status(philosopher, "has taken a fork");
    ft_print_status(philosopher, "is eating");
    pthread_mutex_lock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
    philosopher->last_meal_time = (get_time_in_ms() - philosopher->simulation_start_time);
    if (philosopher->simulation_data->meals_required)
        philosopher->meals_eaten++;
    pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
    ft_usleep(philosopher, philosopher->simulation_data->time_to_eat);
    pthread_mutex_unlock(philosopher->left_fork_mutex);
    pthread_mutex_unlock(philosopher->right_fork_mutex);
}

/* eating:
*	Determines whether the philosopher should use the odd or even dining routine.
*	Calls `dining_of_odd_id` or `dining_of_even_id` based on the philosopher's ID.
*/
void	eating(t_philosopher *philosopher)
{
    if ((philosopher->philosopher_id % 2))
        dining_of_odd_id(philosopher);
    else
        dining_of_even_id(philosopher);
}

/* sleeping:
*	Prints the philosopher's sleeping status.
*	Pauses the thread for the specified sleep duration.
*/
void	sleeping(t_philosopher *philosopher)
{
    ft_print_status(philosopher, "is sleeping");
    ft_usleep(philosopher, philosopher->simulation_data->time_to_sleep);
}

/* thinking:
*	Prints the philosopher's thinking status.
*	Allows the philosopher to think before attempting to eat again.
*/
void	thinking(t_philosopher *data)
{
    if (data->simulation_data->num_philosophers % 2)
        ft_usleep(data, 5);
	ft_print_status(data, "is thinking");
}
