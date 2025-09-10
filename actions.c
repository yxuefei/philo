/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 21:51:01 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_behav(int phi_id, char *s, t_philo *philo)
{
	size_t	tm;

	pthread_mutex_lock(philo->print_mtx);
	tm = ft_gettime() - philo->start_time;
	if (!ft_finish(philo))
	{
		printf("%zu %d %s\n", tm, phi_id, s);
	}
	pthread_mutex_unlock(philo->print_mtx);
}

void	ft_one_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print_behav(philo->phi_id, "has taken a fork", philo);
	ft_usleep(philo->time_die);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print_behav(philo->phi_id, "has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	ft_print_behav(philo->phi_id, "has taken a fork", philo);
	philo->eating = 1;
	ft_print_behav(philo->phi_id, "is eating", philo);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal_time = ft_gettime();
	philo->meal_nbr++;
	pthread_mutex_unlock(philo->meal_mtx);
	ft_usleep(philo->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_behav(philo->phi_id, "is sleeping", philo);
	ft_usleep(philo->time_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print_behav(philo->phi_id, "is thinking", philo);
}
