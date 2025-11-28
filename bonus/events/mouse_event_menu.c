/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 07:30:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 04:25:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool	is_xy_on_button(int x, int y, t_button *btn)
{
	if (x > btn->position.x && x < btn->position.x + btn->width)
		if (y > btn->position.y && y < btn->position.y + btn->height)
			return (true);
	return (false);
}

static bool	is_xy_on_text_button(int x, int y, t_text_button *btn)
{
	if (x > btn->position.x && x < btn->position.x + btn->width)
		if (y > btn->position.y && y < btn->position.y + btn->height)
			return (true);
	return (false);
}

void	mouse_click_main_pause(int x, int y, t_main *g)
{
	if (g->main_menu.btn_continue.height != -1)
	{
		if (is_xy_on_button(x, y, &g->main_menu.btn_continue))
			activate_button(g);
	}
	if (is_xy_on_button(x, y, &g->main_menu.btn_campaign))
		activate_button(g);
	if (is_xy_on_button(x, y, &g->main_menu.btn_map_select))
		g->state = MENU_MAP_SELECT;
	if (is_xy_on_button(x, y, &g->main_menu.btn_exit))
		activate_button(g);
}

void	mouse_click_map_select(int x, int y, t_main *g)
{
	t_text_button	*page;
	int				i;

	if (is_xy_on_text_button(x, y, &g->map_select.prev_page))
	{
		prev_page(g);
		return ;
	}
	if (is_xy_on_text_button(x, y, &g->map_select.next_page))
	{
		next_page(g);
		return ;
	}
	page = g->map_select.maps[g->map_select.curr_page];
	i = -1;
	while (++i < MAP_SELECT_PAGE_NUM)
	{
		if (page[i].width > 0 && is_xy_on_text_button(x, y, &page[i]))
		{
			g->map_select.selected = &page[i];
			activate_button(g);
			return ;
		}
	}
}

void	mouse_click_shop(int x, int y, t_main *g)
{
	int	i;

	if (is_xy_on_text_button(x, y, &g->shop_menu.to_continue))
	{
		g->shop_menu.selected = &g->shop_menu.to_continue;
		activate_button(g);
		return ;
	}
	i = -1;
	while (++i < 6)
	{
		if (is_xy_on_text_button(x, y, &g->shop_menu.items[i]))
		{
			g->shop_menu.selected = &g->shop_menu.items[i];
			activate_button(g);
			return ;
		}
	}
}
