#include "philo.h"

/* get_time_in_ms:
*	Returns the current time in milliseconds.
*	Uses the `gettimeofday` function to calculate the time.
*	Useful for tracking elapsed time in the simulation.
*/
long long	get_time_in_ms(void)
{
    struct timeval		tv;
    long long			m_sec;

    gettimeofday(&tv, NULL);
    m_sec = tv.tv_sec * 1000;
    m_sec += (tv.tv_usec / 1000);
    return (m_sec);
}

/* ft_usleep:
*	Pauses the execution of the current thread for a specified number of milliseconds.
*	Checks periodically if the simulation has stopped to allow early exit.
*	Uses a busy-wait loop with `usleep` for finer control.
*/
void	ft_usleep(t_philosopher *philosopher, long long milliseconds)
{
    long long	start;

    start = (get_time_in_ms() - philosopher->simulation_start_time);
    while ((get_time_in_ms() - philosopher->simulation_start_time) - start < milliseconds)
    {
        pthread_mutex_lock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
        if (philosopher->simulation_data->simulation_stopped)
        {
            pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
            return ;
        }
        pthread_mutex_unlock(&(philosopher->simulation_data->write_and_meal_mutexes[1]));
        usleep(500);
    }
}
