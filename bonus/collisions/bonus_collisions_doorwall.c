/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions_doorwall.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:39:00 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:53:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_collisions.h"
#include <math.h>

static t_segment	extend_segment(t_segment seg, double extension)
{
	t_vector	dir;
	double		len;
	t_segment	result;

	dir.x = seg.e.x - seg.s.x;
	dir.y = seg.e.y - seg.s.y;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= len;
	dir.y /= len;
	result.s.x = seg.s.x - dir.x * extension;
	result.s.y = seg.s.y - dir.y * extension;
	result.e.x = seg.e.x + dir.x * extension;
	result.e.y = seg.e.y + dir.y * extension;
	return (result);
}

static double	check_doorwall_inner_walls(t_cast_data *d, t_door_wall *dw)
{
	t_segment	wall;
	double		dist1;
	double		dist2;

	wall = extend_segment(dw->inner_wall_1, PLAYER_RADIUS / 2);
	dist1 = find_collision_distance(d, wall);
	wall = extend_segment(dw->inner_wall_2, PLAYER_RADIUS / 2);
	dist2 = find_collision_distance(d, wall);
	if (dist1 < dist2)
		return (dist1);
	return (dist2);
}

double	find_doorwall_collision(t_cast_data *d, char **map)
{
	t_door_wall	*dw;
	double		min_dist;
	double		dist;
	int			x;
	int			y;

	min_dist = 1000.0;
	y = (int)d->player->pos.y - 1 - 1;
	while (++y <= (int)d->player->pos.y + 1)
	{
		x = (int)d->player->pos.x - 1 - 1;
		while (++x <= (int)d->player->pos.x + 1)
		{
			if (y >= 0 && map[y] && x >= 0 && map[y][x] == 'D')
			{
				dw = find_door_wall(x, y, NULL);
				if (!dw)
					continue ;
				dist = check_doorwall_inner_walls(d, dw);
				if (dist < min_dist)
					min_dist = dist;
			}
		}
	}
	return (min_dist);
}
