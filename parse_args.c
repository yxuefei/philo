/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:36:02 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/06 16:44:15 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_one(char *s, int *out)
{
	return (ft_atoi_strict(s, out));
}

int	parse_args(int argc, char **argv, t_rules *r)
{
	int	tmp;

	if (argc != 5 && argc != 6)
		return (1);
	if (parse_one(argv[1], &r->n_philo) || r->n_philo <= 0)
		return (1);
	if (parse_one(argv[2], &tmp) || tmp <= 0)
		return (1);
	r->t_die = (t_ms)tmp;
	if (parse_one(argv[3], &tmp) || tmp <= 0)
		return (1);
	r->t_eat = (t_ms)tmp;
	if (parse_one(argv[4], &tmp) || tmp <= 0)
		return (1);
	r->t_sleep = (t_ms)tmp;
	if (argc == 6)
	{
		if (parse_one(argv[5], &r->must_eat) || r->must_eat <= 0)
			return (1);
	}
	else
		r->must_eat = -1;
	r->stop = 0;
	r->finished = 0;
	r->forks = NULL;
	r->philos = NULL;
	return (0);
}
