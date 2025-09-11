/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:41:20 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/11 14:34:25 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//%zu is for size_t
void	ft_print_actions(int phi_id, char *s, t_philo *philo)
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
	ft_print_actions(philo->phi_id, "has taken a fork", philo);
	ft_usleep(philo->time_die);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print_actions(philo->phi_id, "has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	ft_print_actions(philo->phi_id, "has taken a fork", philo);
	philo->eating = 1;
	ft_print_actions(philo->phi_id, "is eating", philo);
	pthread_mutex_lock(philo->meal_mtx);
	philo->last_meal_time = ft_gettime();
	philo->meal_nbr++;
	pthread_mutex_unlock(philo->meal_mtx);
	ft_usleep(philo->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

// void ft_eat(t_philo *p)
// {
//     pthread_mutex_t *first, *second;

//     if (p->l_fork < p->r_fork) {
//         first = p->l_fork;
//         second = p->r_fork;
//     } else {
//         first = p->r_fork;
//         second = p->l_fork;
//     }
//     pthread_mutex_lock(first);
//     ft_print_actions(p->phi_id, "has taken a fork", p);
//     if (ft_finish(p)) {
//         pthread_mutex_unlock(first);
//         return;
//     }
// 	ft_usleep(1);
//     pthread_mutex_lock(second);
//     ft_print_actions(p->phi_id, "has taken a fork", p);
//     if (ft_finish(p)) {
//         pthread_mutex_unlock(second);
//         pthread_mutex_unlock(first);
//         return;
//     }
//     p->eating = 1;
//     ft_print_actions(p->phi_id, "is eating", p);
//     pthread_mutex_lock(p->meal_mtx);
//     p->last_meal_time = ft_gettime();
//     p->meal_nbr++;
//     pthread_mutex_unlock(p->meal_mtx);

//     ft_usleep(p->time_eat);
//     p->eating = 0;
//     pthread_mutex_unlock(second);
//     pthread_mutex_unlock(first);
// }

void	ft_sleep(t_philo *philo)
{
	ft_print_actions(philo->phi_id, "is sleeping", philo);
	ft_usleep(philo->time_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print_actions(philo->phi_id, "is thinking", philo);
}
