/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:47:05 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:51:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_collisions.h"
#include <math.h>
#include <stdio.h>

static void	init_cast_data(t_cast_data *d, t_main *g, double dx, double dy)
{
	d->player = &g->map.player;
	d->door_walls = g->map.door_walls;
	d->map_pos.x = (int)d->player->pos.x;
	d->map_pos.y = (int)d->player->pos.y;
	init_ray_axis(dx, &d->ray_d.x, &d->delta_dist.x);
	init_ray_axis(dy, &d->ray_d.y, &d->delta_dist.y);
	init_x_axis_direction(d);
	init_y_axis_direction(d);
}

static double
	get_min_collision_distance(t_cast_data *d, t_main *g, double max_check)
{
	double	wall_distance;
	double	doorwall_distance;
	double	object_distance;

	wall_distance
		= find_wall_collision(d, g->map.player.pos, g->map.matrix, max_check);
	doorwall_distance = find_doorwall_collision(d, g->map.matrix);
	object_distance = find_object_collision(d, g);
	if (doorwall_distance < wall_distance)
		wall_distance = doorwall_distance;
	if (object_distance < wall_distance)
		wall_distance = object_distance;
	return (wall_distance);
}

static double	check_single_axis(t_cast_data *d, t_main *g, double movement)
{
	double	abs_movement;
	double	min_dist;
	double	max_move;
	double	sign;

	abs_movement = fabs(movement);
	if (abs_movement < 0.0001)
		return (0);
	min_dist
		= get_min_collision_distance(d, g, abs_movement + PLAYER_RADIUS + 1.5);
	max_move = min_dist - PLAYER_RADIUS;
	if (max_move <= 0)
		return (0);
	sign = 1.0;
	if (movement <= 0)
		sign = -1.0;
	if (abs_movement <= max_move)
		return (movement);
	return (max_move * sign);
}

t_vector	check_collision(t_main *g, t_vector movement)
{
	t_cast_data	d;
	t_vector	ret;

	if (fabs(movement.x) >= 0.0001)
	{
		init_cast_data(&d, g, movement.x, 0);
		ret.x = check_single_axis(&d, g, movement.x);
	}
	else
		ret.x = 0;
	if (fabs(movement.y) >= 0.0001)
	{
		init_cast_data(&d, g, 0, movement.y);
		ret.y = check_single_axis(&d, g, movement.y);
	}
	else
		ret.y = 0;
	return (ret);
}
