/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_event_navigations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:32:58 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/22 03:29:10 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "../../events/events.h"

void	next_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
		next_main_pause_item(g);
	else if (g->state == MENU_SHOP)
		next_shop_item(g);
	else if (g->state == MENU_MAP_SELECT)
		next_map_select_item(g);
}

void	prev_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
		prev_main_pause_item(g);
	else if (g->state == MENU_SHOP)
		prev_shop_item(g);
	else if (g->state == MENU_MAP_SELECT)
		prev_map_select_item(g);
}

void	activate_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
		activate_button_main_pause(g);
	else if (g->state == MENU_MAP_SELECT)
		activate_button_map_select(g);
	else if (g->state == MENU_SHOP)
		activate_button_shop(g);
}
