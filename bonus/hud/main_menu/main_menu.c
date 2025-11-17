/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:50:08 by root              #+#    #+#             */
/*   Updated: 2025/11/17 15:57:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"

void *init_main_menu(t_main *g, t_main_menu *mmenu)
{
	g->state = MENU_MAIN;
	mmenu->selected = &mmenu->btn_campaign;
    mmenu->bg_img = g->gallery.mmenu_bg;
    
	mmenu->btn_continue.height = -1;
    set_button(&mmenu->btn_campaign, &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4), (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3});

	set_button(&mmenu->btn_map_select, &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3 + g->gallery.mmenu_start_btn.height});

    set_button(&mmenu->btn_exit, &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2) / 3 + g->gallery.mmenu_start_btn.height * 2});
}

void switch_menu(t_main *g)
{
	if (g->state == MENU_PAUSE || g->state == MENU_MAIN)
	{
		g->state = GAME;
		mlx_mouse_hide(g->window.mlx, g->window.win);
	}
	else if (g->state == GAME)
	{
		g->state = MENU_PAUSE;
		mlx_mouse_show(g->window.mlx, g->window.win);
	}
	else if (g->state == MENU_MAP_SELECT)
		g->state = MENU_MAIN;
    system(AUDIO_MAIN_MENU);
}

// void	render_main_menu(t_main *g)
// {	
// 	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 0);
// 	draw_button(&g->window, &g->gallery.mmenu_start_btn, 0, 0);
// 	draw_button_hover(&g->window, &g->gallery.mmenu_start_btn, 0, g->gallery.mmenu_start_btn.height);
// 	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
// }
