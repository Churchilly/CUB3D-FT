/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_orb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:23:08 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:54:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static void	draw_orb_column(t_main *g, int x, t_ray *ray, t_orb *orb)
{
	int			height;
	double		hit_position;
	t_draw_pkg	pkg;
	int			y_offset;

	height = (int)(WIN_HEIGHT / ray->distance * 0.25 * 0.5);
	y_offset = 200;
	pkg.start = (WIN_HEIGHT / 2) - (height / 2) + y_offset;
	if (pkg.start < 0)
		pkg.start = 0;
	pkg.end = (WIN_HEIGHT / 2) + (height / 2) + y_offset;
	if (pkg.end >= WIN_HEIGHT)
		pkg.end = WIN_HEIGHT - 1;
	hit_position = get_hit_position(ray, &orb->segment);
	pkg.col = get_image_column(hit_position, &g->gallery.misc.pokeball);
	pkg.height = height;
	pkg.image = &g->gallery.misc.pokeball;
	draw_column(&pkg, x, &g->window);
}

void	render_orb(t_main *g, t_orb *orb)
{
	t_cast_data	d;
	t_ray		ray;
	int			x;
	t_ray		*old_ray;

	init_object_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		old_ray = get_ray_from_list(&g->rays, x);
		d.ray_d.x = cos(d.direction);
		d.ray_d.y = sin(d.direction);
		if (!find_intersection(&d, orb->segment))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);
		if (d.ray->distance <= old_ray->distance)
			draw_orb_column(g, x, &ray, orb);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}
