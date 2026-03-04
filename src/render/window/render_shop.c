/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:02:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:31:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdio.h>

void	render_shop(t_main *g)
{
	char	buf[16];

	draw_image_no_alpha(&g->window, &g->gallery.menu_bg.shop, 0, 0);
	draw_image_no_alpha_scaled(&g->window, &g->gallery.hud.currency,
		(t_pos){WIN_WIDTH / 10 - (g->gallery.hud.currency.width * 0.075),
		(WIN_HEIGHT / 7) * 4 - (g->gallery.hud.currency.height * 0.025)}, 0.05);
	snprintf(buf, sizeof(buf), "%d", g->map.player.inventory.currency);
	draw_text(buf, (t_text){2, WIN_WIDTH / 10 - 17.5, (WIN_HEIGHT / 7) * 4 - 16,
		&g->font_menu.alagard, 0, 0, 1.25, &g->window, GOLD_COLOR});
	place_text_button(g, &g->shop_menu.items[0], "Adrenaline Potion - 50g");
	place_text_button(g, &g->shop_menu.items[1], "Mana Increase - 100g");
	place_text_button(g, &g->shop_menu.items[2], "Health Increase - 100g");
	place_text_button(g, &g->shop_menu.items[3], "Damage Increase - 75g");
	place_text_button(g, &g->shop_menu.items[4], "Cooldown Decreaser - 80g");
	place_text_button(g, &g->shop_menu.items[5], "Spinning Orb - 150g");
	place_text_button(g, &g->shop_menu.to_continue, "Continue");
}
