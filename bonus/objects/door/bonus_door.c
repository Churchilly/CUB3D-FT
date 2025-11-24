/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 10:56:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "../../collisions/bonus_collisions.h"
#include <stddef.h>
#include <math.h>
#include <stdio.h>

t_door_wall	*find_door_wall(int x, int y, t_door_wall *new)
{
	static t_door_wall *door_walls = NULL;
	static int count = 0;
	int	i;

	if (x == -1 && new)
	{
		count = y;
		door_walls = new;
		return (NULL);
	}
	if (x == -1)
	{
		if (y < count)
			return (&(door_walls[y]));
		return (NULL);
	}
	i = -1;
	while (++i < count)
	{
		if (x == door_walls[i].map_pos.x && y == door_walls[i].map_pos.y)
			return (&door_walls[i]);
	}
	return (NULL);
}


static void	init_data(t_cast_data *d, t_player *p)
{
	d->player = p;
	d->ray_d.x = cos(p->dov);
	d->ray_d.y = sin(p->dov);
}
// return door in player fov && distance < door_interact_distance
// if no door found returns null
t_door	*find_interactable_door(t_main *g)
{
	t_cast_data	d;
	t_obj_node	*curr;
	t_door		*closest_door;
	double		min_dist;
	double		dist;

	init_data(&d, &g->map.player);
	closest_door = NULL;
	min_dist = DOOR_INTERACT_DISTANCE;
	curr = g->objects.o_dynamic;
	while (curr)
	{
		if (curr->type == DOOR)
		{
			dist = find_collision_distance(&d, ((t_door *)curr->object)->barrier);
			if (dist < min_dist)
			{
				min_dist = dist;
				closest_door = (t_door *)curr->object;
			}
		}
		curr = curr->next;
	}
	return (closest_door);
}
