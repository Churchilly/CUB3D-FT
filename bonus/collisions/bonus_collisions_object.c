/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:40:58 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:47:28 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_collisions.h"

double	find_object_collision(t_cast_data *d, t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;
	double		min_dist;
	double		dist;

	curr = g->objects.all;
	min_dist = 1000.0;
	while (curr)
	{
		if (curr->type == DOOR)
		{
			door = (t_door *)curr->object;
			if (door->state != OPEN)
			{
				dist = find_collision_distance(d, door->barrier);
				if (dist < min_dist)
					min_dist = dist;
			}
		}
		curr = curr->next;
	}
	return (min_dist);
}
