#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation
{
    int				num_philosophers;
    int				time_to_die;
    int				time_to_eat;
    int				num_meals;
    int				time_to_sleep;
    int				simulation_stopped;
    int				meals_required;
    pthread_mutex_t	write_and_meal_mutexes[2];
    pthread_mutex_t	*fork_mutexes;
}	t_simulation;

typedef struct s_philosopher
{
    int				philosopher_id;
    int				meals_eaten;
    long long		last_meal_time;
    long long		simulation_start_time;
    pthread_mutex_t	*right_fork_mutex;
    pthread_mutex_t	*left_fork_mutex;
    t_simulation	*simulation_data;
}	t_philosopher;

void			ft_putstr_fd(int fd, char *str);
int				ft_atoi(const char *str);
int				ft_error(int flag);
int				check_is_digit(char **av);
long long		get_time_in_ms(void);
void			ft_print_status(t_philosopher *philosopher, char *str);
void			*ft_routine_philosopher(void *args);
void			ft_create_threads(t_philosopher **philosophers);
t_philosopher	**init_each_philosopher(t_simulation *simulation);
void			ft_free(t_philosopher **address, int count);
void			ft_memory_management(t_simulation *simulation, \
                                        t_philosopher **philosophers);
void			ft_usleep(t_philosopher *philosopher, long long milliseconds);
void			*death_angel(void *add);
void			eating(t_philosopher *philosopher);
void			thinking(t_philosopher *philosopher);
void			sleeping(t_philosopher *philosopher);
#endif
