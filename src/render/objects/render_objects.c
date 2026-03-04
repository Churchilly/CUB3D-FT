/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:12:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:01:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	render_objects(t_main *g)
{
	t_obj_node	*curr;

	clear_render_queue(&g->objects);
	create_render_queue(g);
	curr = g->objects.to_render;
	while (curr)
	{
		if (curr->type == DOOR)
			render_door(g, curr->object);
		else if (curr->type == FIREBALL)
			render_fireball(g, curr->object);
		else if (curr->type == PARTICLE)
			render_particle(g, curr->object);
		else if (curr->type == ENEMY)
			render_enemy(g, curr->object);
		else if (curr->type == ORB)
			render_orb(g, curr->object);
		curr = curr->next_render;
	}
}
