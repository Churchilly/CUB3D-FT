/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_animation_walk.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:33:13 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/11 17:30:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	reset_walk_animation_vertical(t_main *g)
{
	if (g->spellbook.win_pos.x > g->spellbook.original_win_pos.x)
	{
		g->spellbook.win_pos.x -= SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.x < g->spellbook.original_win_pos.x)
			g->spellbook.win_pos.x = g->spellbook.original_win_pos.x;
	}
	else if (g->spellbook.win_pos.x < g->spellbook.original_win_pos.x)
	{
		g->spellbook.win_pos.x += SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.x > g->spellbook.original_win_pos.x)
			g->spellbook.win_pos.x = g->spellbook.original_win_pos.x;
	}	
}

void	reset_walk_animation_horizontal(t_main *g)
{
	if (g->spellbook.win_pos.y > g->spellbook.original_win_pos.y)
	{
		g->spellbook.win_pos.y -= SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.y < g->spellbook.original_win_pos.y)
			g->spellbook.win_pos.y = g->spellbook.original_win_pos.y;
	}
	else if (g->spellbook.win_pos.y < g->spellbook.original_win_pos.y)
	{
		g->spellbook.win_pos.y += SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.y > g->spellbook.original_win_pos.y)
			g->spellbook.win_pos.y = g->spellbook.original_win_pos.y;
	}	
}

static void	walk_animation_horizontal(t_main *g)
{
	if (g->key_list.w)
	{
		g->spellbook.win_pos.y += SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.y > g->spellbook.original_win_pos.y + SPELLBOOK_WALK_ANIM_MAX)
			g->spellbook.win_pos.y = g->spellbook.original_win_pos.y + SPELLBOOK_WALK_ANIM_MAX;
	}
	if (g->key_list.s)
	{
		g->spellbook.win_pos.y -= SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.y < g->spellbook.original_win_pos.y - SPELLBOOK_WALK_ANIM_MAX)
			g->spellbook.win_pos.y = g->spellbook.original_win_pos.y - SPELLBOOK_WALK_ANIM_MAX;
	}
	if ((!g->key_list.w && !g->key_list.s) || (g->key_list.w && g->key_list.s))
		reset_walk_animation_horizontal(g);
}

static void	walk_animation_vertical(t_main *g)
{
	if (g->key_list.a)
	{
		g->spellbook.win_pos.x += SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.x > g->spellbook.original_win_pos.x + SPELLBOOK_WALK_ANIM_MAX)
			g->spellbook.win_pos.x = g->spellbook.original_win_pos.x + SPELLBOOK_WALK_ANIM_MAX;
	}
	if (g->key_list.d)
	{
		g->spellbook.win_pos.x -= SPELLBOOK_WALK_ANIM_SPEED;
		if (g->spellbook.win_pos.x < g->spellbook.original_win_pos.x - SPELLBOOK_WALK_ANIM_MAX)
			g->spellbook.win_pos.x = g->spellbook.original_win_pos.x - SPELLBOOK_WALK_ANIM_MAX;
	}
	if ((!g->key_list.a && !g->key_list.d) || (g->key_list.a && g->key_list.d))
		reset_walk_animation_vertical(g);
}

void	walk_animation(t_main *g)
{
	walk_animation_horizontal(g);
	walk_animation_vertical(g);
}
