/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:22:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 03:33:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	insert_barrier(t_door *door, t_vector_int map_pos, double axis)
{
	if (axis == 0) // horizontal
	{
		door->barrier.s.x = map_pos.x + 0.5;
		door->barrier.s.y = map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		door->barrier.e.x = map_pos.x + 0.5;
		door->barrier.e.y = door->barrier.s.y + DOOR_WIDTH;
	}
	else // vertical
	{
		door->barrier.s.x = map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		door->barrier.s.y = map_pos.y + 0.5;
		door->barrier.e.x = door->barrier.s.x + DOOR_WIDTH;
		door->barrier.e.y = map_pos.y + 0.5;
	}
	door->state = D_CLOSE;
	door->alpha = DOOR_ALPHA_LOCKED;
	door->color = DOOR_COLOR_LOCKED;
}

void	create_barriers(t_main *g)
{
	t_door_wall *door_walls;
	t_door		*door;
	int			i;

	door_walls = g->map.door_walls;
	if (!door_walls)
		return ;
	i = 0;
	while (door_walls[i].map_pos.x != -1 || door_walls[i].map_pos.y != -1)
	{
		door = alloc(sizeof(t_door), DYNAMIC);
		insert_barrier(door, door_walls[i].map_pos, door_walls[i].axis);
		add_object(&g->objects, DOOR, door, DYNAMIC);
		i++;
	}
}