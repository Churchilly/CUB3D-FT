/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_potions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 19:42:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

//
// void	put_pixel(int x, int y, int color, t_window *win);

static void	draw_potion(t_main *g, int potion)
{
	t_cub3_image	*img;

	img = &g->gallery.misc.potion;
	if (potion == -1)
	{
		draw_image_scaled(&g->window, img, (t_pos){POTIONS_POS_X,
			POTIONS_POS_Y}, .08);
		return ;
	}
	draw_image_no_alpha_scaled(&g->window, img, (t_pos){WIN_WIDTH - (img->width
			* .08), POTIONS_POS_Y + potion * (img->height * .08) + POTION_GAP},
		.08);
}

void	draw_potions(t_main *g)
{
	int	potion_count;
	int	i;

	potion_count = g->map.player.inventory.adrenaline_potions;
	if (potion_count <= 0)
	{
		draw_potion(g, -1);
		return ;
	}
	i = 0;
	while (i < potion_count)
	{
		draw_potion(g, i);
		i++;
	}
}
