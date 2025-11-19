/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:50:08 by root              #+#    #+#             */
/*   Updated: 2025/11/18 23:37:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"
#include "../main/main.h"

void	*init_main_menu(t_main *g, t_main_menu *mmenu)
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

void	*init_map_select_menu(t_main *g, t_map_select *menu)
{
	// 10 button in total
	// 8 buttons for maps 
	// 2 buttons for change page
}
// show up when you complete the map and there is a next map
void	*init_shop_menu(t_main *g, t_map_select *menu)
{
	// 6 buttons in total
}
// shows up when game session ends no matter if u died or won(somehow)
void	*init_game_summary_menu(t_main *g, t_map_select *menu)
{
	// no buttons
	// game summary:
	// how many enemy you have killed
	// How many fireball you have cast
	// what items you have bought on shop and how much
	// how many steps you take
	// how much time passed
	// maybe show them up animated ??
	// 
}
// shows up when map facing with an error while loading map
void	*init_error_menu(t_main *g, t_map_select *menu)
{
	// no buttons
	// 2 text
	// first text says "Failed to load map"
	// second says "click any button to continue"
}