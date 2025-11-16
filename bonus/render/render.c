/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/16 08:54:23 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <math.h>
#include <stdio.h>

static void render_main_menu(t_main *g)
{
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 50);
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, -100);
	place_button(g, &g->main_menu.btn_start);
	place_button(g, &g->main_menu.btn_exit);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

static void render_game(t_main *g)
{
	static int frame_count = 0;
	static long long time_log = 0;
	long long curr_time;

	render_background(g);
	render_scene(g);
	animate_objects(g);
	render_objects(g);
	// do raycasting and store its data
	// according to raycasting data
	// render walls and image that you make
	// put all this shit on screen yay

	draw_mmap(g);
	draw_mana_bar(g);
	draw_heath_bar(g);
	animate_spellbook(g);
	render_spellbook(g);
	render_frames(g);
	draw_image(&g->window, &g->gallery.cross,
		WIN_WIDTH / 2 - g->gallery.cross.width / 2,
		WIN_HEIGHT / 2 - g->gallery.cross.height / 2);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);

	frame_count++;
	curr_time = current_time_ms();

	if (curr_time - time_log >= 1000)
	{
		printf("%ifps\n", frame_count);
		frame_count = 0;
		time_log = curr_time;
	}
}

void	cub_render(t_main *g)
{
	if (g->main_menu.active)
		render_main_menu(g);
	else
		render_game(g);
}
