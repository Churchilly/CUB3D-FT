/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:44:50 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/12 20:47:01 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	next_spell(t_main *g)
{
	if (g->spellbook.changing_direction != 0)
		return ;
	g->spellbook.changing_direction = 1;
	g->spellbook.cooldown = SPELL_COOLDOWN;
}

void	prev_spell(t_main *g)
{
	if (g->spellbook.changing_direction != 0)
		return ;
	g->spellbook.changing_direction = -1;
	g->spellbook.cooldown = SPELL_COOLDOWN;
}

void	cast_spell(t_main *g)
{
	use_mana(g, 42.0);
	if (g->spellbook.cooldown > 0 || g->spellbook.changing_direction != 0)
	{
		if (g->spellbook.cooldown > 0)
			printf("spell in cooldown :: %d\n", g->spellbook.cooldown);
		return ;
	}
	if (g->spellbook.current == FIRBALL)
	{
		system(AUDIO_FIREBALL);
		cast_fireball(g);
	}
	else if (g->spellbook.current == LOCK)
		cast_lock(g);
	else if (g->spellbook.current == UNLOCK)
		cast_unlock(g);
}
