/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_animation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:31:52 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/12 21:18:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static void	idle_animation(t_spellbook *book)
{
	static int	timer = 0;

	if (timer < SPELLBOOK_IDLE_ANIM_SIZE)
		book->win_pos.y += SPELLBOOK_IDLE_ANIM_SPEED;
	else
		book->win_pos.y -= SPELLBOOK_IDLE_ANIM_SPEED;
	timer++;
	if (timer >= SPELLBOOK_IDLE_ANIM_SIZE * 2)
		timer = 0;
}

static int	check_walking(t_main *g, int *phase, int *idle_delay)
{
	if (g->key_list.w || g->key_list.s || g->key_list.d || g->key_list.a)
	{
		walk_animation(g);
		*phase = 3;
		*idle_delay = 0;
		return (1);
	}
	if (*phase == 3)
	{
		reset_walk_animation_horizontal(g);
		reset_walk_animation_vertical(g);
		if (g->spellbook.win_pos.y == g->spellbook.original_win_pos.y
			&& g->spellbook.win_pos.x == g->spellbook.original_win_pos.x)
			*phase = 0;
		*idle_delay = 0;
		return (1);
	}
	return (0);
}

void	animate_spellbook(t_main *g)
{
	static int	phase = 0;
	static int	idle_delay = 0;

	if (g->spellbook.cooldown > 0)
		g->spellbook.cooldown--;
	if (g->spellbook.changing_direction != 0 && (phase == 0 || phase == 3))
		phase = 1;
	if (phase == 1 || phase == 2)
	{
		change_animation(&g->spellbook, &phase, g);
		idle_delay = 0;
		return ;
	}
	if (check_walking(g, &phase, &idle_delay))
		return ;
	if (idle_delay++ < SPELLBOOK_IDLE_START_DELAY)
		return ;
	idle_animation(&g->spellbook);
}
