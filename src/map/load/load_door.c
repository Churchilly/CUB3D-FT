/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 04:21:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/30 02:57:56 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>
#include <stdlib.h>

static int	count_doors(char *raw_map)
{
	int	ret;

	ret = 0;
	while (*raw_map)
	{
		if (*raw_map == 'd' || *raw_map == 'D')
			ret++;
		raw_map++;
	}
	return (ret);
}

static void	insert_inner_walls(t_door_wall *dw)
{
	if (dw->axis == 0)
	{
		dw->inner_wall_1.s.x = dw->map_pos.x;
		dw->inner_wall_1.s.y = dw->map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		dw->inner_wall_1.e.x = dw->map_pos.x + 1.0;
		dw->inner_wall_1.e.y = dw->map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		dw->inner_wall_2.s.x = dw->map_pos.x;
		dw->inner_wall_2.s.y = dw->map_pos.y + 0.5 + (DOOR_WIDTH / 2.0);
		dw->inner_wall_2.e.x = dw->map_pos.x + 1.0;
		dw->inner_wall_2.e.y = dw->map_pos.y + 0.5 + (DOOR_WIDTH / 2.0);
	}
	else
	{
		dw->inner_wall_1.s.x = dw->map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		dw->inner_wall_1.s.y = dw->map_pos.y;
		dw->inner_wall_1.e.x = dw->map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		dw->inner_wall_1.e.y = dw->map_pos.y + 1.0;
		dw->inner_wall_2.s.x = dw->map_pos.x + 0.5 + (DOOR_WIDTH / 2.0);
		dw->inner_wall_2.s.y = dw->map_pos.y;
		dw->inner_wall_2.e.x = dw->map_pos.x + 0.5 + (DOOR_WIDTH / 2.0);
		dw->inner_wall_2.e.y = dw->map_pos.y + 1.0;
	}
}

static int	new_door(int *x, int *y, int c, t_door_wall *dw)
{
	if (c == '\n')
	{
		(*x) = 0;
		(*y)++;
	}
	else if (c == 'd' || c == 'D')
	{
		dw->map_pos.x = (*x);
		dw->map_pos.y = (*y);
		if (c == 'd')
			dw->axis = 0;
		else
			dw->axis = 1;
		insert_inner_walls(dw);
		(*x)++;
		return (1);
	}
	else
		(*x)++;
	return (0);
}

static t_door_wall	*create_door_walls(char *raw_map, int count)
{
	t_door_wall	*door_walls;
	int			x;
	int			y;
	int			i;

	door_walls = alloc(sizeof(t_door_wall) * (count + 1), DYNAMIC);
	x = 0;
	y = 0;
	i = 0;
	while (*raw_map)
	{
		if (new_door(&x, &y, *raw_map, &(door_walls[i])))
			i++;
		raw_map++;
	}
	door_walls[count].map_pos.x = -1;
	door_walls[count].map_pos.y = -1;
	return (door_walls);
}

void	load_doors(char *raw_map, t_main *game)
{
	t_door_wall	*door_walls;
	int			count;

	count = count_doors(raw_map);
	if (count == 0)
	{
		game->map.door_walls = NULL;
		return ;
	}
	door_walls = create_door_walls(raw_map, count);
	game->map.door_walls = door_walls;
}
