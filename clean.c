/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:48:17 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 21:48:34 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *s)
{
	printf("%s", s);
	exit(EXIT_FAILURE);
}

void	ft_clean(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead_mtx);
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->meal_mtx);
	while (i < data->philo->phi_nbr)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}