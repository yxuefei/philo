/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:40:00 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/06 17:39:33 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_rules *r, int i)
{
	t_ms	now, last;

	now = now_ms();
	pthread_mutex_lock(&r->state_mtx);
	last = r->philos[i].last_meal_ms;
	pthread_mutex_unlock(&r->state_mtx);
	if (now - last > r->t_die)
	{
		pthread_mutex_lock(&r->print_mtx);
		if (!r->stop)
		{
			printf("%lld %d died\n", elapsed_ms(r->start_ms), r->philos[i].id);
			pthread_mutex_lock(&r->state_mtx);
			r->stop = 1;
			pthread_mutex_unlock(&r->state_mtx);
		}
		pthread_mutex_unlock(&r->print_mtx);
		return (1);
	}
	return (0);
}


static int	all_full(t_rules *r)
{
	int	ok;

	if (r->must_eat == -1)
		return (0);
	pthread_mutex_lock(&r->state_mtx);
	ok = (r->finished == r->n_philo);
	pthread_mutex_unlock(&r->state_mtx);
	return (ok);
}

void	*monitor_routine(void *arg)
{
	t_rules	*r;
	int		i;

	r = (t_rules *)arg;
	msleep_until(r->start_ms);
	while (!get_stop(r))
	{
		if (all_full(r))
		{
			set_stop(r, 1);
			break ;
		}
		i = 0;
		while (i < r->n_philo && !get_stop(r))
		{
			if (check_death(r, i))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
