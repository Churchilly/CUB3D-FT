/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 08:46:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../events/events.h"
#include <math.h>
#include <stdio.h>

void	render_pause_menu(t_main *g)
{
	// change the fucking images
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	place_button(g, &g->main_menu.btn_continue);
	place_button(g, &g->main_menu.btn_campaign);
	place_button(g, &g->main_menu.btn_map_select);
	place_button(g, &g->main_menu.btn_exit);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	render_main_menu(t_main *g)
{
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	place_button(g, &g->main_menu.btn_campaign);
	place_button(g, &g->main_menu.btn_map_select);
	place_button(g, &g->main_menu.btn_exit);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
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
	draw_image(&g->window, &g->gallery.cross,
		WIN_WIDTH / 2 - g->gallery.cross.width / 2,
		WIN_HEIGHT / 2 - g->gallery.cross.height / 2);

	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	render_select_map(t_main *g)
{
	t_text_button	*page;
	int				i;
	int				idx;

	/* draw background */
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	
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

	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	render_shop(t_main *g)
{
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	place_text_button(g, &g->shop_menu.items[0], "Adrenaline Potion");
	place_text_button(g, &g->shop_menu.items[1], "Mana Increase");
	place_text_button(g, &g->shop_menu.items[2], "Health Increase");
	place_text_button(g, &g->shop_menu.items[3], "Damage Increase");
	place_text_button(g, &g->shop_menu.items[4], "Cooldown Decreaser");
	place_text_button(g, &g->shop_menu.items[5], "Spinning Orb");
	place_text_button(g, &g->shop_menu.to_continue, "Continue");
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	render_error_menu(t_main *g)
{
	static double scale_dir = 0.0075;

	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	draw_text("Failed to load map", g->error_menu.error_text);
	g->error_menu.to_continue.scale += scale_dir;
	g->error_menu.to_continue.win_x = WIN_WIDTH / 2 - (g->error_menu.to_continue.font->font_size * g->error_menu.to_continue.scale * (g->error_menu.to_continue.text_len + 2)) / 3;
	if (g->error_menu.to_continue.scale >= 1.0)
		scale_dir = -0.005;
	else if (g->error_menu.to_continue.scale <= 0.75)
		scale_dir = 0.0075;
	draw_text("Press any key to continue", g->error_menu.to_continue);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	render_summary_menu(t_main *g)
{
	(void)g;
}