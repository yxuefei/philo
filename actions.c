/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 19:50:21 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void take_forks(t_philo *p)
// {
//     int first;
//     int second;

//     if ((p->id % 2) == 1)
//     {
//         first = p->left;
//         second = p->right;
//     }
//     else
//     {
//         first = p->right;
//         second = p->left;
//     }
//     pthread_mutex_lock(&p->rules->forks[first].mtx);
//     log_status(p, ACT_FORK);
//     pthread_mutex_lock(&p->rules->forks[second].mtx);
//     log_status(p, ACT_FORK);
// }


// static void	put_forks(t_philo *p)
// {
// 	pthread_mutex_unlock(&p->rules->forks[p->left].mtx);
// 	pthread_mutex_unlock(&p->rules->forks[p->right].mtx);
// }

static void	mark_meal(t_philo *p)
{
	pthread_mutex_lock(&p->rules->state_mtx);
    p->eating = 1;
	p->last_meal_ms = now_ms();
	pthread_mutex_unlock(&p->rules->state_mtx);
}

static void	count_meal(t_philo *p)
{
	pthread_mutex_lock(&p->rules->state_mtx);
	p->meals += 1;
    p->eating = 0;
	if (p->rules->must_eat != -1 && p->meals == p->rules->must_eat)
		p->rules->finished += 1;
	pthread_mutex_unlock(&p->rules->state_mtx);
}

static void	do_eat(t_philo *p)
{
    mark_meal(p);
	if (!log_status(p, ACT_EAT))
		return ;
	msleep_intr(p->rules, p->rules->t_eat);
	count_meal(p);
}

static void	do_sleep_think(t_philo *p)
{
	if (!log_status(p, ACT_SLEEP))
		return ;
	msleep_intr(p->rules, p->rules->t_sleep);
	log_status(p, ACT_THINK);
}

static void	run_single(t_philo *p)
{
	pthread_mutex_lock(&p->rules->forks[p->left].mtx);
	log_status(p, ACT_FORK);
	while (!get_stop(p->rules))
		usleep(100);
	pthread_mutex_unlock(&p->rules->forks[p->left].mtx);
}

// void    *philo_routine(void *arg)
// {
//     t_philo *p;

//     p = (t_philo *)arg;
//     msleep_until(p->rules->start_ms);
//     if (p->rules->n_philo == 1)
//         return (run_single(p), NULL);
//     if (p->id % 2 == 1)
//         msleep_intr(p->rules, p->rules->t_eat);
//     while (!get_stop(p->rules))
//     {
        
//         if (get_stop(p->rules))
//             break ;
//         // take_forks(p);
// 		// acquire_slot(p->rules);
// 		t_rules *r = p->rules;
// 		int first  = (p->id % 2) ? p->left  : p->right;
// 		int second = (p->id % 2) ? p->right : p->left;

// 		pthread_mutex_lock(&r->forks[first].mtx);
// 		log_status(p, ACT_FORK);

// 		/* ---- 现在才占 slot（最多 99 个）---- */
// 		acquire_slot(r);
// 		if (get_stop(r))
// 		{
// 			pthread_mutex_unlock(&r->forks[first].mtx);
// 			break ;
// 		}

// 		/* ---- 再锁第二把叉子 ---- */
// 		pthread_mutex_lock(&r->forks[second].mtx);
// 		log_status(p, ACT_FORK);

// 		// printf("[%lld] P%d got food\n", elapsed_ms(p->rules->start_ms), p->id);
//         do_eat(p);
// 		// printf("[%lld] P%d got food\n", elapsed_ms(p->rules->start_ms), p->id);
//         put_forks(p);

//         // usleep(200);
//         release_slot(p->rules);
//         do_sleep_think(p);
//         usleep(80); 
//     }
//     return (NULL);
// }

/* Replace the existing philo_routine in actions.c with this version */

/* Paste this to replace the existing loop in philo_routine (actions.c) */

void    *philo_routine(void *arg)
{
    t_philo *p;
    t_rules *r;
    int     first;
    int     second;

    p = (t_philo *)arg;
    r = p->rules;
    msleep_until(r->start_ms);
    if (r->n_philo == 1)
        return (run_single(p), NULL);
    /* stagger start as before */
    if (p->id % 2 == 1)
        msleep_intr(r, r->t_eat);

    while (!get_stop(r))
    {
        acquire_slot(r);
        if (get_stop(r))
        {
            release_slot(r);
            break;
        }

        first  = (p->id % 2) ? p->left  : p->right;
        second = (p->id % 2) ? p->right : p->left;

        pthread_mutex_lock(&r->forks[first].mtx);
        /* if stop was set while acquiring, clean up */
        if (get_stop(r))
        {
            pthread_mutex_unlock(&r->forks[first].mtx);
            break ;
        }
        if (!log_status(p, ACT_FORK)) /* print and also early check */
        {
            pthread_mutex_unlock(&r->forks[first].mtx);
            break ;
        }

        pthread_mutex_lock(&r->forks[second].mtx);
        if (get_stop(r))
        {
            pthread_mutex_unlock(&r->forks[second].mtx);
            pthread_mutex_unlock(&r->forks[first].mtx);
            break ;
        }
        if (!log_status(p, ACT_FORK))
        {
            pthread_mutex_unlock(&r->forks[second].mtx);
            pthread_mutex_unlock(&r->forks[first].mtx);
            break ;
        }

        do_eat(p);
        pthread_mutex_unlock(&r->forks[first].mtx);
        pthread_mutex_unlock(&r->forks[second].mtx);
        release_slot(r);
        do_sleep_think(p);

        usleep(80);
    }
    return (NULL);
}
