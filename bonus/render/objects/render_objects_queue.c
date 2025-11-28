/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects_queue.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 03:02:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:45:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	create_render_queue(t_main *g)
{
	t_obj_node	*curr;

	curr = g->objects.o_static;
	while (curr)
	{
		if (curr->type == FIREBALL)
			queue_add_fireball(curr, g);
		else if (curr->type == ENEMY)
			queue_add_enemy(curr, g);
		else if (curr->type == PARTICLE)
			queue_add_particle(curr, g);
		curr = curr->next;
	}
	curr = g->objects.o_dynamic;
	while (curr)
	{
		if (curr->type == DOOR)
			queue_add_door(curr, g);
		else if (curr->type == ORB)
			queue_add_orb(curr, g);
		curr = curr->next;
	}
}
