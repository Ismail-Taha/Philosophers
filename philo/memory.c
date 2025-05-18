#include "philo.h"

/* ft_free:
*	Frees the memory allocated for an array of philosopher pointers.
*	Iterates through the array and frees each philosopher, then frees the array itself.
*/
void	ft_free(t_philosopher **address, int count)
{
    int	i;

    i = 0;
    while (i < count)
    {
        free(address[i]);
        i++;
    }
    free(address);
}

/* ft_memory_management:
*	Cleans up all allocated resources at the end of the simulation.
*	Destroys all mutexes, frees philosopher structures, and frees the simulation structure.
*/
void	ft_memory_management(t_simulation *simulation, t_philosopher **philosophers)
{
    int	count;

    count = 0;
    while (count < simulation->num_philosophers)
    {
        pthread_mutex_destroy(&(simulation->fork_mutexes[count]));
        count++;
    }
    pthread_mutex_destroy(&(simulation->write_and_meal_mutexes[0]));
    pthread_mutex_destroy(&(simulation->write_and_meal_mutexes[1]));
    ft_free(philosophers, simulation->num_philosophers);
    free(simulation->fork_mutexes);
    free(simulation);
}
