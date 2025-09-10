/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:51:06 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 13:01:56 by xueyang          ###   ########.fr       */
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

typedef long long       t_ms;

typedef enum e_act
{
    ACT_FORK,
    ACT_EAT,
    ACT_SLEEP,
    ACT_THINK,
    ACT_DIED
}   t_act;

struct s_rules;

typedef struct s_fork
{
    pthread_mutex_t     mtx;
}   t_fork;

typedef struct s_philo
{
    int                 id;
    int                 left;
    int                 right;
    int                 meals;
    t_ms                last_meal_ms;
    pthread_t           thread;
    struct s_rules      *rules;
}   t_philo;

typedef struct s_rules
{
    int                 n_philo;
    t_ms                t_die;
    t_ms                t_eat;
    t_ms                t_sleep;
    int                 must_eat;

    t_ms                start_ms;
    int                 stop;
    int                 finished;

    t_fork              *forks;
    pthread_mutex_t     print_mtx;
    pthread_mutex_t     state_mtx;

    t_philo             *philos;
    pthread_t           monitor;
	
    int					slots;
}   t_rules;

/* parsing / init / destroy */
int     parse_args(int argc, char **argv, t_rules *r);
int     init_rules(t_rules *r);
int     init_entities(t_rules *r);
void    destroy_all(t_rules *r);

/* time helpers */
t_ms    now_ms(void);
t_ms    elapsed_ms(t_ms since);
void    msleep_until(t_ms target_ms);
void    msleep(t_ms ms);

/* state / logging */
int     get_stop(t_rules *r);
void    set_stop(t_rules *r, int v);
int     log_status(t_philo *p, t_act act);

/* routines */
void    *philo_routine(void *arg);
void    *monitor_routine(void *arg);

/* utils */
int     ft_atoi_strict(const char *s, int *out);
int     min_int(int a, int b);
int     max_int(int a, int b);

void	acquire_slot(t_rules *r);
void	release_slot(t_rules *r);
void	msleep_intr(t_rules *r, t_ms ms);

#endif
