#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb_ph;
	int				tm_die;
	int				tm_eat;
	int				nb_meal;
	int				tm_slp;
	int				philo_die;
	int				check;
	pthread_mutex_t	wr_eat[2];
	pthread_mutex_t	*forks;
}	t_philo;

typedef struct s_philo_info
{
	int				id;
	int				n_diner;
	long long		last_time_eating;
	long long		date_of_birth;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_philo			*data_of_philo;
}	t_philo_info;

void			ft_putstr_fd(int fd, char *str);
int				ft_atoi(const char *str);
int				ft_error(int flag);
int				check_is_digit(char **av);
long long		get_time_in_ms(void);
void			ft_print_status(t_philo_info *data, char *str);
void			*ft_routine_philo(void *args);
void			ft_create_threads(t_philo_info **info);
t_philo_info	**init_each_philo(t_philo *life);
void			ft_free(t_philo_info **adress, int how_much);
void			ft_memory_management(t_philo *life_routine, \
										t_philo_info **data);
void			ft_usleep(t_philo_info *data, long long mls);
void			*shinigami(void *add);
void			eating(t_philo_info *data);
void			thinking(t_philo_info *data);
void			sleeping(t_philo_info *data);
#endif
