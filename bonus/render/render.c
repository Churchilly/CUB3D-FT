/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/04 16:39:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../hud/minimap/minimap.h"
#include <math.h>
#include <stdio.h>

void	cub_render(t_main *g)
{
	render_background(g);
	render_scene(g);
	animate_objects(g);
	render_objects(g);
	draw_minimap(g);
	draw_image(&g->window, &g->img, 500, 400);
	render_spellbook(g);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}
