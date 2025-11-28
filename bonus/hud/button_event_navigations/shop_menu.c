/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shop_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:15:57 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:39:17 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	purchase_shop_item(t_main *g, int item_idx)
{
	int			cost;
	const int	costs[6] = {50, 100, 100, 75, 80, 150};

	if (item_idx < 0 || item_idx >= 6)
		return ;
	cost = costs[item_idx];
	if (g->map.player.inventory.currency < cost)
		return ;
	g->map.player.inventory.currency -= cost;
	g->record.purchase_count++;
	if (item_idx == 0)
		g->map.player.inventory.adrenaline_potions++;
	else if (item_idx == 1)
		g->map.player.inventory.mana_increase++;
	else if (item_idx == 2)
		g->map.player.inventory.health_increase++;
	else if (item_idx == 3)
		g->map.player.inventory.damage_increase++;
	else if (item_idx == 4)
		g->map.player.inventory.cooldown_decreaser++;
	else if (item_idx == 5)
		g->map.player.inventory.orb++;
}

void	activate_button_shop(t_main *g)
{
	int	i;

	if (g->shop_menu.selected == &g->shop_menu.to_continue)
	{
		if (g->map.next_map)
			next_map(g);
		return ;
	}
	i = 0;
	while (i < 6)
	{
		if (g->shop_menu.selected == &g->shop_menu.items[i])
		{
			purchase_shop_item(g, i);
			return ;
		}
		i++;
	}
}

void	next_shop_item(t_main *g)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (g->shop_menu.selected == &g->shop_menu.items[i])
		{
			if (i < 5)
				g->shop_menu.selected = &g->shop_menu.items[i + 1];
			else
				g->shop_menu.selected = &g->shop_menu.to_continue;
			return ;
		}
		i++;
	}
	if (g->shop_menu.selected == &g->shop_menu.to_continue)
		g->shop_menu.selected = &g->shop_menu.items[0];
}

void	prev_shop_item(t_main *g)
{
	int	i;

	if (g->shop_menu.selected == &g->shop_menu.to_continue)
	{
		g->shop_menu.selected = &g->shop_menu.items[5];
		return ;
	}
	i = 0;
	while (i < 6)
	{
		if (g->shop_menu.selected == &g->shop_menu.items[i])
		{
			if (i > 0)
				g->shop_menu.selected = &g->shop_menu.items[i - 1];
			else
				g->shop_menu.selected = &g->shop_menu.to_continue;
			return ;
		}
		i++;
	}
}
