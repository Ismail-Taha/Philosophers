#include "philo.h"

/* init_each_philosopher:
*	Initializes an array of philosopher structures.
*	Assigns IDs, forks, and other attributes to each philosopher.
*	Returns a pointer to the array of philosophers.
*/
t_philosopher	**init_each_philosopher(t_simulation *simulation)
{
    int				count;
    t_philosopher	**philosophers;

    count = 0;
    philosophers = malloc(sizeof(t_philosopher *) * simulation->num_philosophers);
    simulation->fork_mutexes = malloc(sizeof(pthread_mutex_t) * simulation->num_philosophers);
    while (count < simulation->num_philosophers)
    {
        pthread_mutex_init(&(simulation->fork_mutexes[count]), NULL);
        philosophers[count] = malloc(sizeof(t_philosopher));
        count++;
    }
    count = 0;
    while (count < simulation->num_philosophers)
    {
        philosophers[count]->last_meal_time = 0;
        philosophers[count]->simulation_data = simulation;
        philosophers[count]->philosopher_id = count + 1;
        philosophers[count]->right_fork_mutex = &(simulation->fork_mutexes[count]);
        philosophers[count]->left_fork_mutex = &(simulation->fork_mutexes[(count + 1) % simulation->num_philosophers]);
        philosophers[count]->meals_eaten = 0;
        philosophers[count]->simulation_start_time = get_time_in_ms();
        count++;
    }
    return (philosophers);
}

/* ft_create_threads:
*	Creates threads for each philosopher and the shinigami (monitoring) thread.
*	Waits for all threads to finish execution before cleaning up.
*/
void	ft_create_threads(t_philosopher **philosophers)
{
    int			count;
    pthread_t	*threads;

    threads = malloc(sizeof(pthread_t) * (*philosophers)->simulation_data->num_philosophers);

    count = 0;
    while (count < (*philosophers)->simulation_data->num_philosophers)
    {
        pthread_create(&(threads[count]), NULL, &ft_routine_philosopher, philosophers[count]);
        count++;
    }
    shinigami(philosophers);
    count = 0;
    while ((*philosophers)->simulation_data->num_philosophers > count)
    {
        pthread_join(threads[count], NULL);
        count++;
    }
    free(threads);
}
