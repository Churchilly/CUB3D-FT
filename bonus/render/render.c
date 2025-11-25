/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 16:51:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../events/events.h"
#include <math.h>
#include <stdio.h>

void	render_pause_menu(t_main *g)
{
	// change the fucking images
	draw_image(&g->window, &g->gallery.menu.bg, 0, 50);
	draw_image(&g->window, &g->gallery.menu.bg, 0, -100);
	place_button(g, &g->main_menu.btn_continue);
	place_button(g, &g->main_menu.btn_campaign);
	place_button(g, &g->main_menu.btn_map_select);
	place_button(g, &g->main_menu.btn_exit);
}

void	render_main_menu(t_main *g)
{
	draw_image(&g->window, &g->gallery.menu.bg, 0, 50);
	draw_image(&g->window, &g->gallery.menu.bg, 0, -100);
	place_button(g, &g->main_menu.btn_campaign);
	place_button(g, &g->main_menu.btn_map_select);
	place_button(g, &g->main_menu.btn_exit);
}

void	render_game(t_main *g)
{
	render_background(g);
	render_scene(g);
	render_objects(g);
	draw_mmap(g);
	draw_mana_bar(g);
	draw_heath_bar(g);
	render_spellbook(g);
	render_frames(g);
	draw_image(&g->window, &g->gallery.misc.cross,
		WIN_WIDTH / 2 - g->gallery.misc.cross.width / 2,
		WIN_HEIGHT / 2 - g->gallery.misc.cross.height / 2);
	render_map_time(g);
}

void	render_select_map(t_main *g)
{
	t_text_button	*page;
	int				i;
	int				idx;

	/* draw background */
	draw_image(&g->window, &g->gallery.menu.bg, 0, 50);
	draw_image(&g->window, &g->gallery.menu.bg, 0, -100);
	
	page = NULL;
	if (g->map_select.maps && g->map_select.curr_page >= 0)
		page = g->map_select.maps[g->map_select.curr_page];

	i = 0;
	while (i < MAP_SELECT_PAGE_NUM)
	{
		if (page && page[i].width > 0)
		{
			idx = g->map_select.curr_page * MAP_SELECT_PAGE_NUM + i;
			place_text_button(g, &page[i], g->map.files[idx].file_shown);
		}
		i++;
	}
	place_text_button(g, &g->map_select.prev_page, "<");
	place_text_button(g, &g->map_select.next_page, ">");
}

void	render_shop(t_main *g)
{
	char buf[16];
	draw_image(&g->window, &g->gallery.menu.bg, 0, 50);
	draw_image(&g->window, &g->gallery.menu.bg, 0, -100);
	draw_image_no_alpha_scaled(&g->window, &g->gallery.hud.currency, WIN_WIDTH / 2 - 60, 20, 0.05);
	snprintf(buf, sizeof(buf), "%d", g->map.player.inventory.currency);
	draw_text(buf, (t_text){2, WIN_WIDTH / 2, 25, &g->font_menu.alagard, 0, 0, 1.5, &g->window, 0xFFD700});
	place_text_button(g, &g->shop_menu.items[0], "Adrenaline Potion - 50g");
	place_text_button(g, &g->shop_menu.items[1], "Mana Increase - 100g");
	place_text_button(g, &g->shop_menu.items[2], "Health Increase - 100g");
	place_text_button(g, &g->shop_menu.items[3], "Damage Increase - 75g");
	place_text_button(g, &g->shop_menu.items[4], "Cooldown Decreaser - 80g");
	place_text_button(g, &g->shop_menu.items[5], "Spinning Orb - 150g");
	place_text_button(g, &g->shop_menu.to_continue, "Continue");
}

void	render_error_menu(t_main *g)
{
	static double scale_dir = 0.0075;

	draw_image(&g->window, &g->gallery.menu.bg, 0, 50);
	draw_image(&g->window, &g->gallery.menu.bg, 0, -100);
	draw_text("Failed to load map", g->error_menu.error_text);
	g->error_menu.to_continue.scale += scale_dir;
	g->error_menu.to_continue.win_x = WIN_WIDTH / 2 - (g->error_menu.to_continue.font->font_size * g->error_menu.to_continue.scale * (g->error_menu.to_continue.text_len + 2)) / 3;
	if (g->error_menu.to_continue.scale >= 1.0)
		scale_dir = -0.005;
	else if (g->error_menu.to_continue.scale <= 0.75)
		scale_dir = 0.0075;
	draw_text("Press any key to continue", g->error_menu.to_continue);
}

void	render_summary_menu(t_main *g)
{
	static double scale_dir = 0.0075;
	char buf[64];
	int minutes;
	int seconds;

	draw_image(&g->window, &g->gallery.menu.bg, 0, 50);
	draw_image(&g->window, &g->gallery.menu.bg, 0, -100);
	minutes = (g->record.play_time / 1000) / 60;
	seconds = (g->record.play_time / 1000) % 60;
	snprintf(buf, sizeof(buf), "Time: %02d:%02d", minutes, seconds);
	draw_text(buf, g->summary_menu.run_time);
	snprintf(buf, sizeof(buf), "Enemies Killed: %u", g->record.kill_count);
	draw_text(buf, g->summary_menu.kill_count);
	snprintf(buf, sizeof(buf), "Total Income: %u", g->record.total_income);
	draw_text(buf, g->summary_menu.total_income);
	snprintf(buf, sizeof(buf), "Items Bought: %u", g->record.purchase_count);
	draw_text(buf, g->summary_menu.items_bought);
	g->summary_menu.to_continue.scale += scale_dir;
	g->summary_menu.to_continue.win_x = WIN_WIDTH / 2 - (g->summary_menu.to_continue.font->font_size * g->summary_menu.to_continue.scale * (g->summary_menu.to_continue.text_len + 2)) / 3;
	if (g->summary_menu.to_continue.scale >= 1.0)
		scale_dir = -0.005;
	else if (g->summary_menu.to_continue.scale <= 0.75)
		scale_dir = 0.0075;
	draw_text("Press any key to continue", g->summary_menu.to_continue);
}
