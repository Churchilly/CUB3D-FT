/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:36:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:53:16 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_collisions.h"
#include <math.h>

void	init_x_axis_direction(t_cast_data *d)
{
	if (d->ray_d.x < 0)
	{
		d->step.x = -1;
		d->side_dist.x = (d->player->pos.x - d->map_pos.x) * d->delta_dist.x;
	}
	else if (d->ray_d.x > 0)
	{
		d->step.x = 1;
		d->side_dist.x = (d->map_pos.x + 1.0 - d->player->pos.x)
			* d->delta_dist.x;
	}
	else
	{
		d->step.x = 0;
		d->side_dist.x = INFINITY_DISTANCE;
	}
}

void	init_y_axis_direction(t_cast_data *d)
{
	if (d->ray_d.y < 0)
	{
		d->step.y = -1;
		d->side_dist.y = (d->player->pos.y - d->map_pos.y) * d->delta_dist.y;
	}
	else if (d->ray_d.y > 0)
	{
		d->step.y = 1;
		d->side_dist.y = (d->map_pos.y + 1.0 - d->player->pos.y)
			* d->delta_dist.y;
	}
	else
	{
		d->step.y = 0;
		d->side_dist.y = INFINITY_DISTANCE;
	}
}

void	init_ray_axis(double delta, double *ray_dir, double *delta_dist)
{
	if (fabs(delta) < 0.0001)
	{
		*ray_dir = 0;
		*delta_dist = INFINITY_DISTANCE;
	}
	else
	{
		if (delta > 0)
			*ray_dir = 1.0;
		else
			*ray_dir = -1.0;
		*delta_dist = fabs(1.0 / *ray_dir);
	}
}
