/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:32:20 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 18:32:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	*init_main_menu(t_main *g, t_main_menu *mmenu)
{
	g->state = MENU_MAIN;
	mmenu->selected = &mmenu->btn_campaign;
	set_button(&g->main_menu.btn_continue, &g->gallery.menu.continue_btn,
		(t_vector){(WIN_WIDTH / 2 - g->gallery.menu.continue_btn.width / 4),
		(WIN_HEIGHT / 2) - (g->gallery.menu.continue_btn.height * 2) / 3
		- g->gallery.menu.maps_btn.height * 1.5});
	set_button(&mmenu->btn_campaign, &g->gallery.menu.campaign_btn,
		(t_vector){(WIN_WIDTH / 2 - g->gallery.menu.campaign_btn.width / 4),
		(WIN_HEIGHT / 2) - (g->gallery.menu.campaign_btn.height * 2) / 3});
	set_button(&mmenu->btn_map_select, &g->gallery.menu.maps_btn,
		(t_vector){(WIN_WIDTH / 2 - g->gallery.menu.maps_btn.width / 4),
		(WIN_HEIGHT / 2) - (g->gallery.menu.maps_btn.height * 2) / 3
		+ g->gallery.menu.maps_btn.height * 1.5});
	set_button(&mmenu->btn_exit, &g->gallery.menu.exit_btn,
		(t_vector){(WIN_WIDTH / 2 - g->gallery.menu.exit_btn.width / 4),
		(WIN_HEIGHT / 2) - (g->gallery.menu.exit_btn.height * 2) / 3
		+ g->gallery.menu.exit_btn.height * 3});
	return (g);
}