/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:43:14 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/25 17:35:36 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static void draw_healing_fx(t_main *g)
{
    t_player *player;
    t_cub3_image *img;
    
    player = &g->map.player;
    img = &g->gallery.misc.healing_fx;
    if (player->healing >= DEFAULT_HEALING)
    {
        draw_image_no_alpha_scaled(&g->window, img, WIN_WIDTH / 2 + 5,
            WIN_HEIGHT / 2 - (img->height * .2) - 5, .2);
    }
}

void update_health(t_main *g)
{
    static long long time_log = 0;
    long long curr_time;
    t_player *player;

    player = &g->map.player;
    if (player->health >= MAX_HEALTH)
    {
        time_log = 0;
        return ;
    }
    draw_healing_fx(g);
    curr_time = current_time_ms();
    if (curr_time - time_log > 1)
    {
        if (player->healing > DEFAULT_HEALING)
            player->healing -= 0.5;
        damage_player(g, -(player->healing));
        time_log = curr_time;
    }
}

void damage_player(t_main *g, double val)
{
    t_player *player;

    player = &g->map.player;
    if (player->health <= val)
    {
        if (player->inventory.adrenaline_potions > 0)
        {
            player->inventory.adrenaline_potions--;
            player->healing = POTION_HEALING;
        }
        player->health = 0;
        return ;
    }
    player->health = g->map.player.health - val;
}