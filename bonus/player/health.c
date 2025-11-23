/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:43:14 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 02:03:56 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void update_health(t_main *g)
{
    static long long time_log = 0;
    long long curr_time;
    
    if (g->map.player.health >= MAX_HEALTH)
    {
        time_log = 0;
        return ;
    }
    curr_time = current_time_ms();
    if (curr_time - time_log > 1)
    {
        damage_player(g, -0.05);
        time_log = curr_time;
    }
}

void damage_player(t_main *g, double val)
{
    if (g->map.player.health <= val)
    {
        g->map.player.health = 0;
        return ;
    }
    g->map.player.health = g->map.player.health - val;
}

