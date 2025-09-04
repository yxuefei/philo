/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:47:02 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/04 15:56:23 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(t_data *data, int argc, char **argv)
{
	data->num_of_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->num_of_times_each_philo_must_eat = atoi(argv[5]);
	else
		data->num_of_times_each_philo_must_eat = -1;
	atomic_store(&data->someone_died, false);
	atomic_store(&data->finished_eating_count, 0);
	atomic_store(&data->start_time, get_time_in_ms());
	data->forks = sem_open("/forks_sem", O_CREAT, 0644, data->num_of_philos);
	data->print_lock = sem_open("/print_lock_sem", O_CREAT, 0644, 1);
	data->philo_pids = malloc(sizeof(pid_t) * data->num_of_philos);
	if (!data->forks || !data->print_lock || !data->philo_pids)
	{
		printf("Error: Semaphore or memory allocation failed\n");
		exit(1);
	}
	return (data);
}

void	cleanup(t_data *data)
{
	sem_close(data->forks);
	sem_unlink("/forks_sem");
	sem_close(data->print_lock);
	sem_unlink("/print_lock_sem");
	free(data->philo_pids);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5)
	{
		printf("Error: Not enough arguments\n");
		return (1);
	}
	data = init_data(&data, argc, argv);
	return (0);
}