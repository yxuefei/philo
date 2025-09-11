/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:51:06 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/11 14:32:25 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define MAX_CASE 250

typedef struct s_philo
{
	pthread_t		thread;
	int				phi_id;
	int				eating;
	int				meal_nbr;
	int				min_meal;
	int				phi_nbr;
	int				*dead_flg;
	size_t			last_meal_time;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_mtx;
	pthread_mutex_t	*meal_mtx;
	pthread_mutex_t	*print_mtx;
}   t_philo;

//dead_mtx to protect dead_flg
//meal_mtx to protect last_meal_time & meal_nbr from monitor thread reading inconsistency
//print_mtx to protect print function from multiple thread writing at the same time
//eating can be protected by meal_mtx as well
typedef struct s_data
{
	int				dead_flg;
	t_philo			*philo;
	pthread_mutex_t	meal_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	dead_mtx;
}   t_data;

void	init_param(t_philo *philo, char **av);
void	data_init(t_philo *philo, t_data *data, pthread_mutex_t *forks,
		char **av);
void	lock_init(t_philo *philo, t_data *data);
void	fork_init(pthread_mutex_t *forks, int phi_nbr);
size_t	ft_gettime(void);
int		ft_create_thread(t_data *data, pthread_mutex_t *forks);
void	*ft_thread_actions(void *val);
void	*ft_monitor(void *val);
int		ft_dead(t_philo *philo);
int		ft_finish(t_philo *philo);
int		check_death(t_philo *philo);
int		reach_min_meal(t_philo *philo);
void	ft_print_actions(int phi_id, char *s, t_philo *philo);
void	ft_one_eat(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
int		ft_check_digit(char **av);
// void	check_valid(char **av);
void	ft_error(char *s);
void	ft_clean(t_data *data, pthread_mutex_t *forks);
int		ft_atoi(char *s);
int		ft_usleep(size_t tm);

#endif
