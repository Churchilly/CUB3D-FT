/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 07:58:09 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static void animate_orbs(t_orb *orb, t_main *g)
{
	static int curr_orb = 0;
	static int gap;
	int start_deg;
	
	if (curr_orb == 0)
		gap = 360 / g->map.player.inventory.orb;
	start_deg = animate_orb_rotation();
	curr_orb++;
	orb->position = orb_position(&g->map.player, start_deg + gap * curr_orb, orb, gap);
	orb_damage(g, orb);
	if (curr_orb == g->map.player.inventory.orb)
		curr_orb = 0;
}

static void	animate_object_clusters(t_main *g)
{
	static long long	time_log = 0;
	long long			curr_time;
	t_obj_node			*obj;

	curr_time = current_time_ms();
	if (curr_time - time_log > 50)
	{
		obj = g->objects.all;
		while (obj)
		{
			if (obj->type == ENEMY)
				animate_enemy_effect((t_enemy *)obj->object, g);
			else if (obj->type == PARTICLE)
				animate_particle_y((t_fire_particle *)obj->object);
			obj = obj->next;
		}
		time_log = curr_time;
	}
}

void	animate_objects(t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;

	curr = g->objects.all;
	while (curr)
	{
		if (curr->type == DOOR)
			animate_door(curr->object);
		else if (curr->type == ENEMY)
			animate_enemy(curr->object, g);
		else if (curr->type == FIREBALL)
			animate_fireball(curr->object, g, &g->gallery);
		else if (curr->type == ORB && g->map.player.inventory.orb > 0)
			animate_orbs(curr->object, g);
		curr = curr->next;
	}
	animate_object_clusters(g);
}
