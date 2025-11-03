/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 16:38:46 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "../main/main.h"
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

void	toggle_door(t_door *door, int op)
{
	// open door
	if (op == OPEN && door->state == CLOSE)
		door->state = OPENING;
	// close door
	if (op == CLOSE && door->state == OPEN)
		door->state = CLOSING;
	// lock door
	if (op == LOCKED && door->state == CLOSE)
		door->state = LOCKED;
	// unlock door
	if (op == CLOSE && door->state == LOCKED)
		door->state = CLOSE;
}

t_door	*get_door_in_view()
{
	return (NULL);
}
