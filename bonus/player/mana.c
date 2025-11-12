/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mana.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:43:14 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/12 19:46:18 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void update_mana(t_main *g)
{
    static long long time_log = 0;
    long long curr_time;
    
    if (g->map.player.mana >= MAX_MANA)
    {
        time_log = 0;
        return ;
    }
    curr_time = current_time_ms();
    if (curr_time - time_log > 1)
    {
        use_mana(g, -0.10);
        time_log = curr_time;
    }
}

void use_mana(t_main *g, double val)
{
    if (g->map.player.mana <= val)
    {
        damage_player(g, val - g->map.player.mana);
        g->map.player.mana = 0;
        return ;
    }
    g->map.player.mana = g->map.player.mana - val;
}

