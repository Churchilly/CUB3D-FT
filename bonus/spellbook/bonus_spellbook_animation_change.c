/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_animation_change.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:34:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/11 14:41:57 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

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
		book->cur_texture = &g->spellbook.texture_fireball;
	else if (book->current == LOCK)
		book->cur_texture = &g->spellbook.texture_lock;
	else if (book->current == UNLOCK)
		book->cur_texture = &g->spellbook.texture_unlock;
}

void	change_animation(t_spellbook *book, int *phase, t_main *g)
{
	if (*phase == 1)
	{
		book->win_pos.y += SPELLBOOK_CHANGE_ANIM_SPEED;
		if (book->win_pos.y >= book->original_win_pos.y + 200)
		{
			change_spell(book, g);
			*phase = 2;
		}
	}
	else if (*phase == 2)
	{
		book->win_pos.y -= SPELLBOOK_CHANGE_ANIM_SPEED;
		if (book->win_pos.y <= book->original_win_pos.y)
		{
			book->win_pos.y = book->original_win_pos.y;
			book->changing_direction = 0;
			*phase = 0;
		}
	}	
}
