/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_render.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:48:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/04 17:23:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
// after texture change remove t_main *g
static void	change_spell(t_spellbook *book, t_main *g)
{
	int	spell;
	
	spell = (int)book->current + book->changing_direction;
	if (spell < 0)
		spell = 2;
	else if (spell > 2)
		spell = 0;
	book->current = (t_spell)spell;
	if (book->current == FIRBALL)
		book->cur_texture = &g->spellbook_fireball;
	else if (book->current == LOCK)
		book->cur_texture = &g->spellbook_lock;
	else if (book->current == UNLOCK)
		book->cur_texture = &g->spellbook_unlock;
}

static void	animation(t_main *g, int *phase, double original_y)
{
	if (*phase == 1)
	{
		g->spellbook.win_pos.y += SPELLBOOK_ANIM_SPEED;
		if (g->spellbook.win_pos.y >= original_y + 200)
		{
			change_spell(&g->spellbook, g);
			*phase = 2;
		}
	}
	else if (*phase == 2)
	{
		g->spellbook.win_pos.y -= SPELLBOOK_ANIM_SPEED;
		if (g->spellbook.win_pos.y <= original_y)
		{
			g->spellbook.win_pos.y = original_y;
			g->spellbook.changing_direction = 0;
			*phase = 0;
		}
	}	
}

static void	idle_animation(t_spellbook *book)
{
	static int	timer = 0;
	
	if (timer < 100)
		book->win_pos.y += SPELLBOOK_IDLE_ANIM_SPEED;
	else
		book->win_pos.y -= SPELLBOOK_IDLE_ANIM_SPEED;
	timer++;
	if (timer >= 200)
		timer = 0;
}

// make idle animation whebook goes up and down little by little
void	animate_spellbook(t_main *g)
{
	static double	original_y = 0;
	static int		phase = 0;

	if (g->spellbook.changing_direction == 0)
	{
		idle_animation(&g->spellbook);
		phase = 0;
		return ;
	}
	if (phase == 0)
	{
		original_y = g->spellbook.win_pos.y;
		phase = 1;
	}
	animation(g, &phase, original_y);
}

void	render_spellbook(t_main *g)
{
	t_texture	*texture;
	int			x;
	int			y;
	int			color;
	int			tex_x;
	int			tex_y;

	if (!g->spellbook.cur_texture)
		return ;
	texture = g->spellbook.cur_texture;
	y = -1;
	while (++y < texture->height / SPELLBOOK_SCALE)
	{
		x = -1;
		while (++x < texture->width / SPELLBOOK_SCALE)
		{
			tex_x = x * SPELLBOOK_SCALE;
			tex_y = y * SPELLBOOK_SCALE;
			color = *(int *)(texture->addr + (tex_y * texture->line_length
					+ tex_x * (texture->bits_per_pixel / 8)));
			if ((color & 0xFFFFFF) != 0)
				put_pixel((int)g->spellbook.win_pos.x + x,
					(int)g->spellbook.win_pos.y + y, color, &g->window);
		}
	}
}
