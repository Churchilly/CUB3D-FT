/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:32:58 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/17 18:42:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	next_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
	{
		if (g->main_menu.selected == &(g->main_menu.btn_continue))
			g->main_menu.selected = &(g->main_menu.btn_campaign);
		else if (g->main_menu.selected == &(g->main_menu.btn_campaign))
			g->main_menu.selected = &(g->main_menu.btn_map_select);
		else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
			g->main_menu.selected = &(g->main_menu.btn_exit);
		else if (g->main_menu.selected == &(g->main_menu.btn_exit))
		{
			if (g->main_menu.btn_continue.height != -1)
				g->main_menu.selected = &(g->main_menu.btn_continue);
			else
				g->main_menu.selected = &(g->main_menu.btn_campaign);
		}
	}
}

void	prev_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
	{
		if (g->main_menu.selected == &(g->main_menu.btn_continue))
			g->main_menu.selected = &(g->main_menu.btn_exit);
		else if (g->main_menu.selected == &(g->main_menu.btn_campaign))
		{
			if (g->main_menu.btn_continue.height != -1)
				g->main_menu.selected = &(g->main_menu.btn_continue);
			else
				g->main_menu.selected = &(g->main_menu.btn_exit);
		}
		else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
			g->main_menu.selected = &(g->main_menu.btn_campaign);
		else if (g->main_menu.selected == &(g->main_menu.btn_exit))
			g->main_menu.selected = &(g->main_menu.btn_map_select);
	}
}


void activate_button(t_main *g)
{

	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
	{
    	if (g->main_menu.selected == &g->main_menu.btn_campaign)
    	{
			// dump the gc that holds the game things here
			init_game(g, CAMPAIGN_MAP); // always init game
			// dump the gc that holds the garbages that are created while initing game (like map_copy or raw_map)
			if (g->main_menu.btn_continue.height == -1)
			{
    			set_button(&g->main_menu.btn_continue,
					&g->gallery.mmenu_start_btn,
    	    		(t_vector){(WIN_WIDTH / 2
					- g->gallery.mmenu_start_btn.width / 4),
    	    	    (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2)
					/ 3 - g->gallery.mmenu_start_btn.height});
			}
			switch_menu(g);
    	    g->key_list.f3.key_switch = true;
    	}
		else if (g->main_menu.selected == &g->main_menu.btn_continue)
			switch_menu(g);
		else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
			g->state = MENU_MAP_SELECT;
    	else if (g->main_menu.selected == &g->main_menu.btn_exit)
    	    terminate_hook();
	}
}
