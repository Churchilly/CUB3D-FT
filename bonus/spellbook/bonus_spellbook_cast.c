/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook_cast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:46:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 10:35:41 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	cast_fireball(t_main *g)
{
	static long long last_cooldown = 0;
	long long curr_time;
	
	g->spellbook.cooldown = SPELL_COOLDOWN;
	t_fireball *fireball;
	t_obj_node *objects;

	// curr_time = current_time_ms();
	// if (curr_time - last_cooldown < SPELL_COOLDOWN)
	// 	return;
	// last_cooldown = curr_time;
	
	objects = g->objects.o_static;
	while (objects)
	{
		if (objects->type == FIREBALL)
		{
			fireball = (t_fireball *)objects->object;
			if (fireball->state == IDLE)
			{
				fireball->position = (t_vector){g->map.player.pos.x, g->map.player.pos.y};
				fireball->direction = g->map.player.dov;
				fireball->state = FLY;
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
