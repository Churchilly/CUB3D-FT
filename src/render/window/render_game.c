/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:01:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:01:46 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	render_game(t_main *g)
{
	render_background(g);
	render_scene(g);
	render_objects(g);
	draw_mmap(g);
	draw_mana_bar(g);
	draw_heath_bar(g);
	draw_potions(g);
	render_spellbook(g);
	render_frames(g);
	draw_image(&g->window, &g->gallery.misc.cross,
		WIN_WIDTH / 2 - g->gallery.misc.cross.width / 2,
		WIN_HEIGHT / 2 - g->gallery.misc.cross.height / 2);
	render_map_time(g);
}
