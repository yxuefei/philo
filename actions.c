/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/06 16:45:19 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *p)
{
	t_rules	*r;

	r = p->rules;
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&r->forks[p->right].mtx);
		log_status(p, ACT_FORK);
		pthread_mutex_lock(&r->forks[p->left].mtx);
		log_status(p, ACT_FORK);
	}
	else
	{
		pthread_mutex_lock(&r->forks[p->left].mtx);
		log_status(p, ACT_FORK);
		pthread_mutex_lock(&r->forks[p->right].mtx);
		log_status(p, ACT_FORK);
	}
}

static void	put_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->rules->forks[p->left].mtx);
	pthread_mutex_unlock(&p->rules->forks[p->right].mtx);
}

static void	mark_meal(t_philo *p)
{
	pthread_mutex_lock(&p->rules->state_mtx);
	p->last_meal_ms = now_ms();
	pthread_mutex_unlock(&p->rules->state_mtx);
}

static void	count_meal(t_philo *p)
{
	pthread_mutex_lock(&p->rules->state_mtx);
	p->meals += 1;
	if (p->rules->must_eat != -1 && p->meals == p->rules->must_eat)
		p->rules->finished += 1;
	pthread_mutex_unlock(&p->rules->state_mtx);
}

static void	do_eat(t_philo *p)
{
	if (!log_status(p, ACT_EAT))
		return ;
	mark_meal(p);
	msleep(p->rules->t_eat);
	count_meal(p);
}

static void	do_sleep_think(t_philo *p)
{
	if (!log_status(p, ACT_SLEEP))
		return ;
	msleep(p->rules->t_sleep);
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

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->rules->n_philo == 1)
		return (run_single(p), NULL);
	msleep_until(p->rules->start_ms);
	if (p->id % 2 == 0)
		usleep(200);
	pthread_mutex_lock(&p->rules->state_mtx);
	p->last_meal_ms = p->rules->start_ms;
	pthread_mutex_unlock(&p->rules->state_mtx);
	while (!get_stop(p->rules))
	{
		take_forks(p);
		do_eat(p);
		put_forks(p);
		do_sleep_think(p);
	}
	return (NULL);
}
