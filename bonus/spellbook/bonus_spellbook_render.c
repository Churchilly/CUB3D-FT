/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_render.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:48:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 20:21:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// make idle animation where spellbook goes up and down little by little
void	animate_spellbook(t_main *g)
{
	static double	original_y = 0;
	static int		phase = 0;

	if (g->spellbook.changing_direction == 0)
	{
		phase = 0;
		return ;
	}
	if (phase == 0)
	{
		original_y = g->spellbook.win_pos.y;
		phase = 1;
	}
	if (phase == 1)
	{
		int	new_spell;

		g->spellbook.win_pos.y += SPELLBOOK_ANIM_SPEED;
		if (g->spellbook.win_pos.y >= original_y + 200)
		{
			// need a seperate function for this changing spell shit xd
			new_spell = (int)g->spellbook.current + g->spellbook.changing_direction;
			if (new_spell < 0)
				new_spell = 2;
			else if (new_spell > 2)
				new_spell = 0;
			g->spellbook.current = (t_spell)new_spell;
			if (g->spellbook.current == FIRBALL)
				g->spellbook.cur_texture = &g->spellbook_fireball;
			else if (g->spellbook.current == LOCK)
				g->spellbook.cur_texture = &g->spellbook_lock;
			else if (g->spellbook.current == UNLOCK)
				g->spellbook.cur_texture = &g->spellbook_unlock;
			phase = 2;
		}
	}
	else if (phase == 2)
	{
		g->spellbook.win_pos.y -= SPELLBOOK_ANIM_SPEED;
		if (g->spellbook.win_pos.y <= original_y)
		{
			g->spellbook.win_pos.y = original_y;
			g->spellbook.changing_direction = 0;
			phase = 0;
		}
	}
}

void	render_spellbook(t_main *g)
{
	t_texture	*texture;
	int			x;
	int			y;
	int			color;
	int			tex_x;
	int			tex_y;
	int			scale;

	if (!g->spellbook.cur_texture)
		return ;
	texture = g->spellbook.cur_texture;
	scale = 4;
	y = -1;
	while (++y < texture->height / scale)
	{
		x = -1;
		while (++x < texture->width / scale)
		{
			tex_x = x * scale;
			tex_y = y * scale;
			color = *(int *)(texture->addr + (tex_y * texture->line_length
					+ tex_x * (texture->bits_per_pixel / 8)));
			if ((color & 0xFFFFFF) != 0)
				put_pixel((int)g->spellbook.win_pos.x + x,
					(int)g->spellbook.win_pos.y + y, color, &g->window);
		}
	}
}
