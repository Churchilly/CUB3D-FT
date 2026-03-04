/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions_calculation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:32:01 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:52:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_collisions.h"
#include <math.h>

double	calculate_wall_distance(t_cast_data *d, t_vector pos, int side)
{
	double	distance;

	if (side == 0)
		distance = (d->map_pos.x - pos.x + ((1 - d->step.x) / 2.0))
			/ d->ray_d.x;
	else
		distance = (d->map_pos.y - pos.y + ((1 - d->step.y) / 2.0))
			/ d->ray_d.y;
	return (fabs(distance));
}

double	find_collision_distance(t_cast_data *d, t_segment wall)
{
	t_vector	wall_d;
	t_vector	ray_d;
	double		det;
	double		dt_wall;
	double		dt_ray;

	wall_d.x = wall.e.x - wall.s.x;
	wall_d.y = wall.e.y - wall.s.y;
	det = d->ray_d.x * wall_d.y - d->ray_d.y * wall_d.x;
	if (fabs(det) < 1e-10)
		return (1000.0);
	ray_d.x = wall.s.x - d->player->pos.x;
	ray_d.y = wall.s.y - d->player->pos.y;
	dt_ray = (ray_d.x * wall_d.y - ray_d.y * wall_d.x) / det;
	dt_wall = (ray_d.x * d->ray_d.y - ray_d.y * d->ray_d.x) / det;
	if (dt_ray > 0 && dt_wall >= 0.0 && dt_wall <= 1.0)
		return (dt_ray);
	return (1000.0);
}

double	calculate_hit_position(t_cast_data *d, t_vector pos, int side)
{
	t_vector	hit;

	if (side == 0)
	{
		hit.x = d->map_pos.x + ((1 - d->step.x) / 2.0);
		hit.y = pos.y + ((hit.x - pos.x) / d->ray_d.x) * d->ray_d.y;
		return (hit.y - floor(hit.y));
	}
	else
	{
		hit.y = d->map_pos.y + ((1 - d->step.y) / 2.0);
		hit.x = pos.x + ((hit.y - pos.y) / d->ray_d.y) * d->ray_d.x;
		return (hit.x - floor(hit.x));
	}
}
