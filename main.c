/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:47:02 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 21:53:27 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_thread(t_data *data, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &ft_monitor, data->philo) != 0)
		ft_clean(data, forks);
	i = 0;
	while (i < data->philo[0].phi_nbr)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &ft_thread_behav,
				&data->philo[i]) != 0)
			ft_clean(data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		ft_clean(data, forks);
	while (i < data->philo[0].phi_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			ft_clean(data, forks);
		i++;
	}
	return (0);
}

void	*ft_thread_behav(void *val)
{
	t_philo	*philo;

	philo = (t_philo *)val;
	if (philo->phi_id % 2 == 0)
		ft_usleep(1);
	while (!ft_finish(philo))
	{
		if (philo->phi_nbr == 1)
			ft_one_eat(philo);
		else
			ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (val);
}

int	main(int ac, char **av)
{
	t_philo			philo[MAX_CASE];
	t_data			data;
	pthread_mutex_t	forks[MAX_CASE];

	if (ac != 5 && ac != 6)
		ft_error("Invalid number of parameter.\n");
	if (ft_check_digit(av))
		ft_error("Input should be positive digits.\n");
	check_valid(av);
	lock_init(philo, &data);
	fork_init(forks, ft_atoi(av[1]));
	data_init(philo, &data, forks, av);
	ft_create_thread(&data, forks);
	ft_clean(&data, forks);
	return (0);
}
