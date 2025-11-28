/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_render.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:48:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 19:54:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdio.h>

void	render_spellbook(t_main *g)
{
	t_texture		*texture;
	t_vector_int	win;
	int				color;
	t_vector_int	text;

	texture = g->spellbook.cur_texture;
	win.y = -1;
	while (++win.y < texture->height / g->spellbook.scale)
	{
		win.x = -1;
		while (++win.x < texture->width / g->spellbook.scale)
		{
			text.x = win.x * g->spellbook.scale;
			text.y = win.y * g->spellbook.scale;
			color = *(int *)(texture->addr + (text.y * texture->line_length
						+ text.x * (texture->bits_per_pixel / 8)));
			if ((color & 0xFFFFFF) != 0)
				put_pixel((int)g->spellbook.win_pos.x + win.x,
					(int)g->spellbook.win_pos.y + win.y, color, &g->window);
		}
	}
}
