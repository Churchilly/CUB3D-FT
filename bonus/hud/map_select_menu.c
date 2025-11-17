/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_select_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:38:46 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/17 21:44:02 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void *init_map_select_menu(t_main *g, t_map_select *mmenu)
{
	g->state = MENU_MAIN;
	mmenu->selected = &mmenu->btn_maps[0];
    mmenu->bg_img = g->gallery.mmenu_bg;
    
    set_button(&mmenu->btn_maps[0], &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4), (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3});

	set_button(&mmenu->btn_maps[1], &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3 + g->gallery.mmenu_start_btn.height});

    set_button(&mmenu->btn_maps[2], &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3 + g->gallery.mmenu_start_btn.height * 2});
	set_button(&mmenu->btn_maps[2], &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3 + g->gallery.mmenu_start_btn.height * 2});
	set_button(&mmenu->btn_maps[2], &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3 + g->gallery.mmenu_start_btn.height * 2});
}