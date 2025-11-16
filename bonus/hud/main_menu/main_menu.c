/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:50:08 by root              #+#    #+#             */
/*   Updated: 2025/11/16 05:15:17 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"

void *init_main_menu(t_main *g, t_main_menu *mmenu)
{
    mmenu->active = true;
    mmenu->bg_img = g->gallery.mmenu_bg;
	mmenu->selected = &mmenu->btn_start;
    
    set_button(&mmenu->btn_start, &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4), 210});
    
    set_button(&mmenu->btn_exit, &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4),
            210 + g->gallery.mmenu_start_btn.height + 5});
}

void switch_main_menu(t_main *g)
{
    g->main_menu.active = !(g->main_menu.active);
    if (g->main_menu.active)
        mlx_mouse_show(g->window.mlx, g->window.win);
    else
        mlx_mouse_hide(g->window.mlx, g->window.win);
    system(AUDIO_MAIN_MENU);
}

// void	render_main_menu(t_main *g)
// {	
// 	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 0);
// 	draw_button(&g->window, &g->gallery.mmenu_start_btn, 0, 0);
// 	draw_button_hover(&g->window, &g->gallery.mmenu_start_btn, 0, g->gallery.mmenu_start_btn.height);
// 	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
// }
