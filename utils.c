/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:14:19 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/06 16:34:01 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_philo *p, t_act act)
{
    if (act == ACT_FORK)
        printf("%lld %d has taken a fork\n", now_ms(), p->id);
    else if (act == ACT_EAT)
        printf("%lld %d is eating\n", now_ms(), p->id);
    else if (act == ACT_SLEEP)
        printf("%lld %d is sleeping\n", now_ms(), p->id);
    else if (act == ACT_THINK)
        printf("%lld %d is thinking\n", now_ms(), p->id);
    else if (act == ACT_DIED)
        printf("%lld %d died\n", now_ms(), p->id);
}

t_ms	now_ms(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
