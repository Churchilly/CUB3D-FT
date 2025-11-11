/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_render.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:48:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/11 17:13:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	render_spellbook(t_main *g)
{
	t_texture	*texture;
	int			x;
	int			y;
	int			color;
	int			tex_x;
	int			tex_y;
		
	texture = g->spellbook.cur_texture;
	y = -1;
	while (++y < texture->height / g->spellbook.scale)
	{
		x = -1;
		while (++x < texture->width / g->spellbook.scale)
		{
			tex_x = x * g->spellbook.scale;
			tex_y = y * g->spellbook.scale;
			color = *(int *)(texture->addr + (tex_y * texture->line_length
					+ tex_x * (texture->bits_per_pixel / 8)));
			if ((color & 0xFFFFFF) != 0)
				put_pixel((int)g->spellbook.win_pos.x + x,
					(int)g->spellbook.win_pos.y + y, color, &g->window);
		}
	}
}
