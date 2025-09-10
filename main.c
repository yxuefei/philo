/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:47:02 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 14:21:39 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(void)
{
	write(2, "Usage: ./philo n t_die t_eat t_sleep ", 38);
	write(2, "[must_eat]\n", 11);
}

static int	start_threads(t_rules *r)
{
	int	i;

	r->start_ms = now_ms() + 50;
	pthread_mutex_lock(&r->state_mtx);
	i = 0;
	while (i < r->n_philo)
	{
		r->philos[i].last_meal_ms = r->start_ms;
		r->philos[i].meals = 0;
		i++;
	}
	pthread_mutex_unlock(&r->state_mtx);
	i = 0;
	while (i < r->n_philo)
	{
		if (pthread_create(&r->philos[i].thread, NULL, \
				philo_routine, &r->philos[i]) != 0)
			return (set_stop(r, 1), 1);
		i++;
	}
	if (pthread_create(&r->monitor, NULL, monitor_routine, r) != 0)
		return (set_stop(r, 1), 1);
	return (0);
}


static void	join_threads(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->n_philo)
	{
		pthread_join(r->philos[i].thread, NULL);
		i++;
	}
	pthread_join(r->monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_rules	r;

	if (parse_args(argc, argv, &r) != 0)
		return (print_usage(), 1);
	if (init_rules(&r) != 0)
		return (write(2, "init_rules failed\n", 18), 1);
	if (init_entities(&r) != 0)
		return (destroy_all(&r), write(2, "init_entities failed\n", 21), 1);
	if (start_threads(&r) != 0)
	{
		join_threads(&r);
		destroy_all(&r);
		return (write(2, "thread start failed\n", 20), 1);
	}
	join_threads(&r);
	destroy_all(&r);
	return (0);
}
