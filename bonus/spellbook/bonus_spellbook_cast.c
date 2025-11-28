/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_cast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:46:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 03:33:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	cast_fireball(t_main *g)
{	
	t_fireball *fireball;
	t_obj_node *objects;

	g->spellbook.cooldown = SPELL_COOLDOWN;
	objects = g->objects.o_static;
	while (objects)
	{
		if (objects->type == FIREBALL)
		{
			fireball = (t_fireball *)objects->object;
			if (fireball->state == F_IDLE)
			{
				fireball->position = (t_vector){g->map.player.pos.x, g->map.player.pos.y};
				fireball->direction = g->map.player.dov;
				fireball->state = F_FLY;
				g->record.fireballs_cast++;
				return ;
			}
		}
		objects = objects->next;
	}
}

void	cast_lock(t_main *g)
{
	t_door	*door;

	door = find_interactable_door(g);
	if (!door)
		return ;
	if (door->state == D_OPEN || door->state == D_UNLOCKING)
	{
		door->state = D_LOCKING;
		g->spellbook.cooldown = SPELL_COOLDOWN;
	}
}

void	cast_unlock(t_main *g)
{
	t_door	*door;

	door = find_interactable_door(g);
	if (!door)
		return ;
	if (door->state == D_CLOSE || door->state == D_LOCKING)
	{
		door->state = D_UNLOCKING;
		g->spellbook.cooldown = SPELL_COOLDOWN;
	}
}
