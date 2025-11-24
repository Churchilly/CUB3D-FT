/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-pause_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:37:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 08:07:02 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	next_main_pause_item(t_main *g)
{
	if (g->main_menu.selected == &(g->main_menu.btn_continue))
		g->main_menu.selected = &(g->main_menu.btn_campaign);
	else if (g->main_menu.selected == &(g->main_menu.btn_campaign))
		g->main_menu.selected = &(g->main_menu.btn_map_select);
	else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
		g->main_menu.selected = &(g->main_menu.btn_exit);
	else if (g->main_menu.selected == &(g->main_menu.btn_exit))
	{
		if (g->state == MENU_PAUSE)
			g->main_menu.selected = &(g->main_menu.btn_continue);
		else
			g->main_menu.selected = &(g->main_menu.btn_campaign);
	}
}

void	prev_main_pause_item(t_main *g)
{
	if (g->main_menu.selected == &(g->main_menu.btn_continue))
		g->main_menu.selected = &(g->main_menu.btn_exit);
	else if (g->main_menu.selected == &(g->main_menu.btn_campaign))
	{
		if (g->state == MENU_PAUSE)
			g->main_menu.selected = &(g->main_menu.btn_continue);
		else
			g->main_menu.selected = &(g->main_menu.btn_exit);
	}
	else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
		g->main_menu.selected = &(g->main_menu.btn_campaign);
	else if (g->main_menu.selected == &(g->main_menu.btn_exit))
		g->main_menu.selected = &(g->main_menu.btn_map_select);
}

void	activate_button_main_pause(t_main *g)
{
	if (g->main_menu.selected == &g->main_menu.btn_campaign)
		new_game(g, CAMPAIGN_MAP);
	else if (g->main_menu.selected == &g->main_menu.btn_continue)
		switch_menu(g);
	else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
		g->state = MENU_MAP_SELECT;
	else if (g->main_menu.selected == &g->main_menu.btn_exit)
		terminate_hook();
}
