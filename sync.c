/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xueyang <xueyang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:02:45 by xueyang           #+#    #+#             */
/*   Updated: 2025/09/10 20:00:47 by xueyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    msleep_intr(t_rules *r, t_ms ms)
{
    t_ms   start;

    start = now_ms();
    while (!get_stop(r) && elapsed_ms(start) < ms)
        usleep(100);
}

// static int  try_acquire_slot_once(t_rules *r)
// {
//     int ok;

//     ok = 0;
//     pthread_mutex_lock(&r->state_mtx);
//     if (r->slots > 0 && !r->stop)
//     {
//         r->slots--;
//         ok = 1;
//     }
//     pthread_mutex_unlock(&r->state_mtx);
//     return (ok);
// }

// void acquire_slot(t_rules *r)
// {
//     while (!get_stop(r))
//     {
//         pthread_mutex_lock(&r->state_mtx);
//         if (r->slots > 0 && !r->stop)
//         {
//             r->slots--;
//             pthread_mutex_unlock(&r->state_mtx);
//             // fprintf(stderr, "DBG_SLOT: acquired -> now %d\n", r->slots);
//             return ;
//         }
//         pthread_mutex_unlock(&r->state_mtx);
//         usleep(200);
//     }
// }


// void release_slot(t_rules *r)
// {
//     pthread_mutex_lock(&r->state_mtx);
//     r->slots++;
//     // if (r->slots > r->n_philo)
//     //     fprintf(stderr, "DBG_SLOT BUG: slots=%d > n_philo=%d\n", r->slots, r->n_philo);
//     pthread_mutex_unlock(&r->state_mtx);
// }


/* sync.c */

// static int try_acquire_slot_once(t_rules *r)
// {
//     int ok = 0;

//     pthread_mutex_lock(&r->state_mtx);
//     if (r->slots > 0 && !r->stop)
//     {
//         r->slots--;
//         ok = 1;
//     }
//     pthread_mutex_unlock(&r->state_mtx);
//     return ok;
// }

void acquire_slot(t_rules *r)
{
    while (!get_stop(r))
    {
        pthread_mutex_lock(&r->state_mtx);
        if (r->slots > 0 && !r->stop)
        {
            r->slots--;
            pthread_mutex_unlock(&r->state_mtx);
            return;
        }
        pthread_mutex_unlock(&r->state_mtx);
        if (r->n_philo > 100)
            usleep(50);
        else
            usleep(100);
    }
}

/* release without logging (keep it minimal) */
void release_slot(t_rules *r)
{
    pthread_mutex_lock(&r->state_mtx);
    r->slots++;
    pthread_mutex_unlock(&r->state_mtx);
}
