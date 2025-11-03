/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions_wall.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:25:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:53:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_collisions.h"
#include <math.h>

static int	check_doorwall_passage(t_cast_data *d, t_vector pos,
		t_door_wall *dw, int side)
{
	double	wall_hit_pos;
	double	door_start;
	double	door_end;

	if (side != dw->axis)
		return (0);
	wall_hit_pos = calculate_hit_position(d, pos, side);
	door_start = (1.0 - DOOR_WIDTH) / 2.0;
	door_end = door_start + DOOR_WIDTH;
	if (wall_hit_pos > door_start && wall_hit_pos < door_end)
		return (1);
	return (0);
}

static void	step_ray(t_cast_data *d, int *side, double *dist)
{
	if (d->side_dist.x < d->side_dist.y)
	{
		d->side_dist.x += d->delta_dist.x;
		d->map_pos.x += d->step.x;
		*side = 0;
		*dist = d->side_dist.x;
	}
	else
	{
		d->side_dist.y += d->delta_dist.y;
		d->map_pos.y += d->step.y;
		*side = 1;
		*dist = d->side_dist.y;
	}
}

static double	check_wall_collision_single(t_cast_data *d, t_vector pos,
		char **map, double max_dist)
{
	int			side;
	double		dist;
	t_door_wall	*dw;

	while (1)
	{
		step_ray(d, &side, &dist);
		if (dist > max_dist)
			break ;
		if (d->map_pos.y < 0 || !map[d->map_pos.y]
			|| d->map_pos.x < 0 || !map[d->map_pos.y][d->map_pos.x])
			break ;
		if (map[d->map_pos.y][d->map_pos.x] == 'D')
		{
			dw = find_door_wall(d->map_pos.x, d->map_pos.y, NULL);
			if (dw && !check_doorwall_passage(d, pos, dw, side))
				return (calculate_wall_distance(d, pos, side));
		}
		if (map[d->map_pos.y][d->map_pos.x] == '1')
			return (calculate_wall_distance(d, pos, side));
	}
	return (1000.0);
}

static void	init_offset_cast_data(t_cast_data *dst, t_cast_data *src,
		t_vector offset_pos)
{
	*dst = *src;
	dst->player = src->player;
	dst->map_pos.x = (int)offset_pos.x;
	dst->map_pos.y = (int)offset_pos.y;
	init_x_axis_direction(dst);
	init_y_axis_direction(dst);
}

double	find_wall_collision(t_cast_data *d, t_vector pos, char **map,
		double max_dist)
{
	t_cast_data	d_offset;
	t_vector	offset_pos;
	double		distances[3];

	distances[0] = check_wall_collision_single(d, pos, map, max_dist);
	offset_pos.x = pos.x + (-d->ray_d.y * PLAYER_RADIUS / 2.0);
	offset_pos.y = pos.y + (d->ray_d.x * PLAYER_RADIUS / 2.0);
	init_offset_cast_data(&d_offset, d, offset_pos);
	distances[1]
		= check_wall_collision_single(&d_offset, offset_pos, map, max_dist);
	offset_pos.x = pos.x + (-d->ray_d.y * PLAYER_RADIUS / 2.0) * -1;
	offset_pos.y = pos.y + (d->ray_d.x * PLAYER_RADIUS / 2.0) * -1;
	init_offset_cast_data(&d_offset, d, offset_pos);
	distances[2]
		= check_wall_collision_single(&d_offset, offset_pos, map, max_dist);
	return (fmin(fmin(distances[0], distances[1]), distances[2]));
}
