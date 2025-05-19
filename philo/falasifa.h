/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   falasifa.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isallali <isallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:27:14 by isallali          #+#    #+#             */
/*   Updated: 2025/05/19 15:27:15 by isallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FALASIFA_H
# define FALASIFA_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	int					meals;
	long long			last_meal_time;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		meal_mtx;
	struct s_prog		*prog;
}						t_philo;

typedef struct s_prog
{
	int					philo_count;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					meals_required;
	long long			start;
	int					dead;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		print_mtx;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	pthread_t			*monitor;
	t_philo				*philos;
	pthread_mutex_t		turn_mtx;
	int					turn;
}						t_prog;

/* time functions */
long					get_time(void);
void					ft_usleep(long ms, t_prog *prog);
int						is_critical_time(t_prog *prog);
/* utility functions */
void					print_state(t_philo *philo, char *state);
int						get_dead(t_prog *prog);
void					set_dead(t_philo *philo);
long					get_last_meal(t_philo *philo);
void					set_last_meal(t_philo *philo);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
/* initialization functions */
int						check_args(int ac, char **av);
int						prog_args_init(t_prog *prog, int ac, char **av);
void					*djikstra_mon(void *arg);
int						prog_init(t_prog *prog);
int						mutexes_init(t_prog *prog);
void					philos_init(t_prog *prog);

/* philosopher actions */
void					take_forks3(t_philo *philo);
int						eat_action(t_philo *philo);
int						eat3_action(t_philo *philo);
int						sleep_think(t_philo *philo);
void					*philo_thread(void *arg);
void					*philo_thread3(void *arg);

/* cleanup functions */
void					prog_clean(t_prog *prog);

#endif /*FALASIFA_H*/