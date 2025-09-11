/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:14:19 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 22:25:13 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// void	check_valid(char **av)
// {
// 	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) >= MAX_CASE)
// 		ft_error("Number of philo is invalid.\n");
// 	if (ft_atoi(av[2]) <= 0)
// 		ft_error("Time to die is invalid.\n");
// 	if (ft_atoi(av[3]) <= 0)
// 		ft_error("Time to eat is invalid.\n");
// 	if (ft_atoi(av[4]) <= 0)
// 		ft_error("Time to sleep is invalid.\n");
// 	if (av[5])
// 	{
// 		if (ft_atoi(av[5]) <= 0)
// 			ft_error("Number of meals is invalid.\n");
// 	}
// }

int	ft_atoi(char *s)
{
	unsigned long	res;
	int				sign;
	int				i;

	res = 0;
	i = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (sign * res);
}

size_t	ft_gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		ft_error("gettimeofday fail");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t tm)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < tm)
	{
		usleep(500);
	}
	return (0);
}
