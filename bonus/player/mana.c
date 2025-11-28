/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mana.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:43:14 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 21:39:53 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void update_mana(t_main *g)
{
    static long long time_log = 0;
    long long curr_time;
    int max_mana;
    
    max_mana = MAX_MANA + g->map.player.inventory.mana_increase * 15;
    if (g->map.player.mana >= max_mana)
    {
        time_log = 0;
        return ;
    }
    curr_time = current_time_ms();
    if (curr_time - time_log > 1)
    {
        use_mana(g, -.3);
        time_log = curr_time;
    }
}

void use_mana(t_main *g, double val)
{
    if (g->spellbook.cooldown > 0 && val > 0)
        return ;
    if (g->map.player.mana <= val)
    {
        damage_player(g, val - g->map.player.mana + (g->map.player.health / 100 * 5));
        g->map.player.mana = 0;
        return ;
    }
    g->map.player.mana = g->map.player.mana - val;
}
