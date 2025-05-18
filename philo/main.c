#include "philo.h"

/* get_simulation_data:
*	Parses command-line arguments and initializes the simulation structure.
*	Allocates memory for the simulation and sets default values.
*	Initializes mutexes for writing and meal tracking.
*/
t_simulation	*get_simulation_data(int argc, char **argv)
{
    t_simulation	*simulation;

    simulation = malloc(sizeof(t_simulation));
    if (!simulation)
        return (NULL);
    simulation->num_philosophers = ft_atoi(argv[1]);
    simulation->time_to_die = ft_atoi(argv[2]);
    simulation->time_to_eat = ft_atoi(argv[3]);
    simulation->time_to_sleep = ft_atoi(argv[4]);
    simulation->meals_required = 0;
    simulation->simulation_stopped = 0;
    pthread_mutex_init(&(simulation->write_and_meal_mutexes[0]), NULL);
    pthread_mutex_init(&(simulation->write_and_meal_mutexes[1]), NULL);
    if (argc == 6)
    {
        simulation->meals_required = 1;
        simulation->num_meals = ft_atoi(argv[5]);
    }
    return (simulation);
}

int	main(int argc, char **argv)
{
    t_simulation	*simulation;
    t_philosopher	**philosophers;

    if (argc == 5 || argc == 6)
    {
        if (check_is_digit(argv))
            return (1);
        simulation = get_simulation_data(argc, argv);
        philosophers = init_each_philosopher(simulation);
        ft_create_threads(philosophers);
        ft_memory_management(simulation, philosophers);
    }
    else
        ft_putstr_fd(2, "Error: invalid number of arguments\n"
                        "Usage: ./philo <number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep> [number_of_times_must_eat]\n");
    return (0);
}
