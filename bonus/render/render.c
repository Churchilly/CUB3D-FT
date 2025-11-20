/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 18:19:14 by yusudemi         ###   ########.fr       */
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
	
}

void	render_error_menu(t_main *g)
{
	//draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	//draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	
	draw_text("Failed to load map", &g->error_menu.error_text);
	
	static long long last_blink = 0;
	static double scale_dir = 0.01;
	long long curr_time;
	
	//curr_time = current_time_ms();
	//if (curr_time - last_blink > 16)
	//{
	//	g->error_menu.to_continue.scale += scale_dir;
	//	if (g->error_menu.to_continue.scale >= 1.2)
	//		scale_dir = -0.01;
	//	else if (g->error_menu.to_continue.scale <= 0.8)
	//		scale_dir = 0.01;
	//	last_blink = curr_time;
	//}
	
	draw_text("Press any key to continue", &g->error_menu.to_continue);
	
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}
