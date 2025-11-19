/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/19 03:42:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
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

	char *text = "CUBCUBCUBCUBCUBCUB";
	draw_text("asdasdasdasdasd", &g->font_menu.alagard, (t_pos){0, 0}, &g->window, 0.5);
	draw_text("asdasdasdasdasd", &g->font_menu.alagard, (t_pos){0, 50}, &g->window, 1);
	draw_text("asdasdasdasdasd", &g->font_menu.alagard, (t_pos){0, 100}, &g->window, 1.5);
	draw_text("asdasdasdasdasd", &g->font_menu.alagard, (t_pos){0, 150}, &g->window, 2);
	draw_text("asdasdasdasdasd", &g->font_menu.alagard, (t_pos){0, 200}, &g->window, 5);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	render_select_map(t_main *g)
{
	place_button(g, &g->main_menu.btn_campaign);
	place_button(g, &g->main_menu.btn_map_select);
	place_button(g, &g->main_menu.btn_exit);	
}

void	render_shop(t_main *g)
{
	
}
