/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_fireball.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:39:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:59:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static void	draw_fireball_column(t_main *g, int x, t_ray *ray,
		t_fireball *fireball)
{
	int			height;
	double		hit_position;
	t_draw_pkg	pkg;

	height = (int)(WIN_HEIGHT / ray->distance * 0.35);
	pkg.start = (WIN_HEIGHT / 2) - (height / 2);
	if (pkg.start < 0)
		pkg.start = pkg.start - (pkg.start * -1) / 2 / 2;
	pkg.end = (WIN_HEIGHT / 2) + (height / 2);
	if (pkg.end >= WIN_HEIGHT)
		pkg.end = WIN_HEIGHT - 1;
	hit_position = get_hit_position(ray, &fireball->segment);
	pkg.col = get_image_column(hit_position, &g->gallery.fireball.fireball);
	pkg.height = height;
	pkg.image = &g->gallery.fireball.fireball;
	draw_column(&pkg, x, &g->window);
}

void	render_fireball(t_main *g, t_fireball *f)
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
		if (!find_intersection(&d, f->segment))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);
		if (d.ray->distance <= old_ray->distance)
			draw_fireball_column(g, x, &ray, f);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}

static void	draw_particle_column(t_main *g, int x, t_ray *ray,
		t_fire_particle *particle)
{
	int			height;
	double		hit_position;
	t_draw_pkg	pkg;

	height = (int)(WIN_HEIGHT / ray->distance * 0.30);
	pkg.start = (WIN_HEIGHT / 2) - (height / 2) / 2 / 2 / 2 + particle->start_y;
	if (pkg.start < 0)
		pkg.start = pkg.start - (pkg.start * -1) / 2 / 2;
	pkg.end = (WIN_HEIGHT / 2) + (height / 2);
	if (pkg.end >= WIN_HEIGHT)
		pkg.end = WIN_HEIGHT - 1;
	hit_position = get_hit_position(ray, &particle->segment);
	pkg.col = get_image_column(hit_position, &g->gallery.fireball.particle_1);
	pkg.height = height;
	pkg.image = &particle->image;
	draw_column(&pkg, x, &g->window);
}

void	render_particle(t_main *g, t_fire_particle *particle)
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
		if (!find_intersection(&d, particle->segment))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);
		if (d.ray->distance <= old_ray->distance)
			draw_particle_column(g, x, &ray, particle);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}
