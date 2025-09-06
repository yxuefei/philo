/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:40:43 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/06 16:45:18 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ms	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((t_ms)tv.tv_sec * 1000LL + (t_ms)(tv.tv_usec / 1000));
}

t_ms	elapsed_ms(t_ms since)
{
	t_ms	now;

	now = now_ms();
	if (now < since)
		return (0);
	return (now - since);
}

void	msleep_until(t_ms target_ms)
{
	while (1)
	{
		if (now_ms() >= target_ms)
			break ;
		usleep(100);
	}
}

void	msleep(t_ms ms)
{
	t_ms	start;

	start = now_ms();
	while (elapsed_ms(start) < ms)
		usleep(100);
}
