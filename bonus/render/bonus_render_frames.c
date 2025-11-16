/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_frames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 08:54:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/16 09:01:15 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void render_frames(t_main *g)
{
    t_im *frame;
    t_player *player;

    player = &g->map.player;
    if (player->health < 20)
        frame = &g->gallery.frames.low_hp_3;
    else if (player->health < 50)
        frame = &g->gallery.frames.low_hp_2;
    else if (player->health < 80)
        frame = &g->gallery.frames.low_hp_1;
    else
        return ;
    draw_image_no_alpha(&g->window, frame, 0, 0);
}
