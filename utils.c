/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:14:19 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 16:39:08 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	print_line(t_rules *r, int id, t_act act)
// {
// 	t_ms	ts;

// 	ts = elapsed_ms(r->start_ms);
// 	if (act == ACT_FORK)
// 		printf("%lld %d has taken a fork\n", ts, id);
// 	else if (act == ACT_EAT)
// 		printf("%lld %d is eating\n", ts, id);
// 	else if (act == ACT_SLEEP)
// 		printf("%lld %d is sleeping\n", ts, id);
// 	else if (act == ACT_THINK)
// 		printf("%lld %d is thinking\n", ts, id);
// 	else if (act == ACT_DIED)
// 		printf("%lld %d died\n", ts, id);
// }

// int	log_status(t_philo *p, t_act act)
// {
// 	int	allowed;

// 	pthread_mutex_lock(&p->rules->print_mtx);
// 	allowed = !get_stop(p->rules) || act == ACT_DIED;
// 	if (allowed)
// 		print_line(p->rules, p->id, act);
// 	pthread_mutex_unlock(&p->rules->print_mtx);
// 	return (allowed);
// }

/* utils.c — 更安全的 log_status：先检查 stop（state_mtx），再打印（print_mtx） */
int log_status(t_philo *p, t_act act)
{
    int allowed;

    /* 先读取 stop，在 state_mtx 下，避免在持有 print_mtx 时再去拿 state_mtx */
    pthread_mutex_lock(&p->rules->state_mtx);
    allowed = !p->rules->stop || act == ACT_DIED;
    pthread_mutex_unlock(&p->rules->state_mtx);

    if (!allowed)
        return (0);

    pthread_mutex_lock(&p->rules->print_mtx);
    if (act == ACT_FORK)
        printf("%lld %d has taken a fork\n", elapsed_ms(p->rules->start_ms), p->id);
    else if (act == ACT_EAT)
        printf("%lld %d is eating\n", elapsed_ms(p->rules->start_ms), p->id);
    else if (act == ACT_SLEEP)
        printf("%lld %d is sleeping\n", elapsed_ms(p->rules->start_ms), p->id);
    else if (act == ACT_THINK)
        printf("%lld %d is thinking\n", elapsed_ms(p->rules->start_ms), p->id);
    else if (act == ACT_DIED)
        printf("%lld %d died\n", elapsed_ms(p->rules->start_ms), p->id);
    pthread_mutex_unlock(&p->rules->print_mtx);
    return (1);
}

int	get_stop(t_rules *r)
{
	int	v;

	pthread_mutex_lock(&r->state_mtx);
	v = r->stop;
	pthread_mutex_unlock(&r->state_mtx);
	return (v);
}

void	set_stop(t_rules *r, int v)
{
	pthread_mutex_lock(&r->state_mtx);
	r->stop = v;
	pthread_mutex_unlock(&r->state_mtx);
}

int	min_int(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_atoi_strict(const char *s, int *out)
{
	long	nb;

	nb = 0;
	if (!s || !*s)
		return (1);
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+')
		s++;
	if (*s < '0' || *s > '9')
		return (1);
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - '0');
		if (nb > INT_MAX)
			return (1);
		s++;
	}
	if (*s != '\0')
		return (1);
	*out = (int)nb;
	return (0);
}
