/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:37:09 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 20:03:07 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_rules *r)
{
	int	i;

	if (pthread_mutex_init(&r->print_mtx, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&r->state_mtx, NULL) != 0)
		return (pthread_mutex_destroy(&r->print_mtx), 1);
	i = 0;
	while (i < r->n_philo)
	{
		if (pthread_mutex_init(&r->forks[i].mtx, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&r->forks[i].mtx);
			pthread_mutex_destroy(&r->state_mtx);
			pthread_mutex_destroy(&r->print_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_rules(t_rules *r)
{
	r->forks = (t_fork *)malloc(sizeof(t_fork) * r->n_philo);
	if (!r->forks)
		return (1);
	r->philos = (t_philo *)malloc(sizeof(t_philo) * r->n_philo);
	if (!r->philos)
		return (free(r->forks), r->forks = NULL, 1);
	if (init_mutexes(r))
		return (free(r->philos), free(r->forks), r->philos = NULL, \
			r->forks = NULL, 1);
    /*
     * To ensure progress without risking deadlock, gate the number of
     * philosophers that may attempt to pick up forks to N-1 for any N >= 2.
     * Using N/2 for large N can cause unnecessary starvation under tight
     * t_die constraints because threads queue for the slot before eating.
     */
	if (r->n_philo == 1)
		r->slots = 1;
	else if (r->n_philo > 100)
		r->slots = r->n_philo / 2;
	else
		r->slots = r->n_philo - 1;
    return (0);
}

int	init_entities(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n_philo)
	{
		r->philos[i].id = i + 1;
		r->philos[i].left = i;
		r->philos[i].right = (i + 1) % r->n_philo;
		r->philos[i].meals = 0;
		r->philos[i].last_meal_ms = 0;
		r->philos[i].rules = r;
		r->philos[i].eating = 0;
		i++;
	}
	return (0);
}

void	destroy_all(t_rules *r)
{
	int	i;

	if (!r)
		return ;
	if (r->forks)
	{
		i = 0;
		while (i < r->n_philo)
			pthread_mutex_destroy(&r->forks[i++].mtx);
	}
	pthread_mutex_destroy(&r->state_mtx);
	pthread_mutex_destroy(&r->print_mtx);
	free(r->philos);
	free(r->forks);
	r->philos = NULL;
	r->forks = NULL;
}
