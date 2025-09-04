/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:51:06 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/04 15:56:21 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <time.h>
# include <stdatomic.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sched.h>
# include <sys/resource.h>
# include <sys/syscall.h>


typedef struct s_data
{
    int				num_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				num_of_times_each_philo_must_eat;
    atomic_bool		someone_died;
    atomic_int		finished_eating_count;
    atomic_long		start_time;
    sem_t			*forks;
    sem_t			*print_lock;
    pid_t			*philo_pids;
}	t_data;

typedef struct s_philo
{
    int				id;
    atomic_long		last_meal_time;
    int				times_eaten;
    t_data			*data;
}	t_philo;

long		get_time_in_ms(void);
void		ft_usleep(int milliseconds);
void		print_action(t_philo *philo, const char *action);
int			ft_atoi(const char *str);
void		cleanup(t_data *data, t_philo *philos);
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data, t_philo **philos);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
int			start_simulation(t_data *data, t_philo *philos);
void		terminate_processes(t_data *data);
int			is_number(const char *str);
void		free_resources(t_data *data, t_philo *philos);
int			error_and_cleanup(t_data *data, t_philo *philos, const char *msg);
int			check_overflow(const char *str);
int			validate_arguments(int argc, char **argv);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(const char *str);
int			ft_isdigit(int c);
int			ft_iswhitespace(int c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strdup(const char *s1);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		**ft_split(const char *s, char c);


#endif