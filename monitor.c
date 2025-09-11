/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:40:00 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/11 14:34:28 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	while (1)
	{
		if (check_death(philo) || reach_min_meal(philo))
			break ;
	}
	return (val);
}

int	ft_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mtx);
	if ((ft_gettime() - philo->last_meal_time >= philo->time_die)
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mtx);
	return (0);
}

int	ft_finish(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mtx);
	if (*philo->dead_flg == 1)
	{
		pthread_mutex_unlock(philo->dead_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_mtx);
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].phi_nbr)
	{
		if (ft_dead(&philo[i]))
		{
			ft_print_actions(philo[i].phi_id, "died", &philo[i]);
			pthread_mutex_lock(philo[0].dead_mtx);
			*philo->dead_flg = 1;
			pthread_mutex_unlock(philo[0].dead_mtx);
			return (1);
		}
		i++;
	}
	return (0);
}

int	reach_min_meal(t_philo *philo)
{
	int	i;
	int	finsh_nbr;

	i = 0;
	finsh_nbr = 0;
	if (philo[0].min_meal == -1)
		return (0);
	while (i < philo[0].phi_nbr)
	{
		pthread_mutex_lock(philo[i].meal_mtx);
		if (philo[i].meal_nbr >= philo[i].min_meal)
			finsh_nbr++;
		pthread_mutex_unlock(philo[i].meal_mtx);
		i++;
	}
	if (finsh_nbr == philo[0].phi_nbr)
	{
		pthread_mutex_lock(philo[0].dead_mtx);
		*philo->dead_flg = 1;
		pthread_mutex_unlock(philo[0].dead_mtx);
		return (1);
	}
	return (0);
}
