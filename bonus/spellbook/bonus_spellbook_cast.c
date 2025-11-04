/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_cast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:46:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/04 16:39:19 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	cast_fireball(t_main *g)
{
	g->spellbook.cooldown = SPELL_COOLDOWN;
	// [BURAK]
}

void	cast_lock(t_main *g)
{
	t_door	*door;

	door = find_interactable_door(g);
	if (!door)
		return ;
	if (door->state == OPEN || door->state == UNLOCKING)
	{
		door->state = LOCKING;
		g->spellbook.cooldown = SPELL_COOLDOWN;
	}
}

void	cast_unlock(t_main *g)
{
	t_door	*door;

	door = find_interactable_door(g);
	if (!door)
		return ;
	if (door->state == CLOSE || door->state == LOCKING)
	{
		door->state = UNLOCKING;
		g->spellbook.cooldown = SPELL_COOLDOWN;
	}
}
