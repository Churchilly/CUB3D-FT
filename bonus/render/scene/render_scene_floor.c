/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:16:53 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:28:55 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static void	init_render_data(t_render_floor_data *d, t_main *g, int x,
		t_ray *ray)
{
	d->floor_tex = &g->map.texture_f;
	d->fov_rad = FOV * M_PI / 180.0;
	d->ray_angle = g->map.player.dov - (d->fov_rad / 2.0) + ((double)x
			/ WIN_WIDTH) * d->fov_rad;
	d->ray_dir.x = cos(d->ray_angle);
	d->ray_dir.y = sin(d->ray_angle);
	d->wall_height = (int)(WIN_HEIGHT / ray->distance);
	d->wall_end = (d->wall_height / 2) + (WIN_HEIGHT / 2);
	if (d->wall_end >= WIN_HEIGHT)
		d->wall_end = WIN_HEIGHT - 1;
}

static int	get_floor_tex_color(t_texture *tex, t_vector pos)
{
	int	tx;
	int	ty;

	tx = (int)(pos.x * tex->width) % tex->width;
	ty = (int)(pos.y * tex->height) % tex->height;
	if (tx < 0)
		tx += tex->width;
	if (ty < 0)
		ty += tex->height;
	return (*(int *)(tex->addr + (ty * tex->line_length + tx
			* (tex->bits_per_pixel / 8))));
}

void	draw_floor_column(t_main *g, int x, t_ray *ray)
{
	t_render_floor_data	d;
	int					y;
	double				row_distance;
	t_vector			floor_pos;
	int					color;

	init_render_data(&d, g, x, ray);
	y = WIN_HEIGHT / 2;
	while (++y < WIN_HEIGHT)
	{
		if (y < d.wall_end)
			continue ;
		row_distance = (WIN_HEIGHT / 2.0) / (y - WIN_HEIGHT / 2.0);
		row_distance /= cos(d.ray_angle - g->map.player.dov);
		floor_pos.x = g->map.player.pos.x + d.ray_dir.x * row_distance;
		floor_pos.y = g->map.player.pos.y + d.ray_dir.y * row_distance;
		color = get_floor_tex_color(d.floor_tex, floor_pos);
		put_pixel(x, y, color, &g->window);
	}
}
