/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mana.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:43:14 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/23 04:28:40 by root             ###   ########.fr       */
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
        use_mana(g, -1);
        time_log = curr_time;
    }
}

void use_mana(t_main *g, double val)
{
    if (g->map.player.mana <= val)
    {
        // damage_player(g, val - g->map.player.mana + (g->map.player.health / 100 * 5));
        g->map.player.mana = 0;
        return ;
    }
    g->map.player.mana = g->map.player.mana - val;
}

