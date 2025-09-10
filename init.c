/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:37:09 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 21:52:57 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_philo *philo, t_data *data, pthread_mutex_t *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].phi_id = i + 1;
		philo[i].eating = 0;
		philo[i].meal_nbr = 0;
		parsing(&philo[i], av);
		philo[i].start_time = ft_gettime();
		philo[i].last_meal_time = ft_gettime();
		philo[i].print_mtx = &data->print_mtx;
		philo[i].meal_mtx = &data->meal_mtx;
		philo[i].dead_mtx = &data->dead_mtx;
		philo[i].dead_flg = &data->dead_flg;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].phi_nbr - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	fork_init(pthread_mutex_t *forks, int phi_nbr)
{
	int	i;

	i = 0;
	while (i < phi_nbr)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	lock_init(t_philo *philo, t_data *data)
{
	data->dead_flg = 0;
	data->philo = philo;
	pthread_mutex_init(&data->dead_mtx, NULL);
	pthread_mutex_init(&data->meal_mtx, NULL);
	pthread_mutex_init(&data->print_mtx, NULL);
}
