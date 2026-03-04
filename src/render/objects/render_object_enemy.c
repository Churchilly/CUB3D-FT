/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_enemy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:26:28 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:53:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static t_im	*get_enemy_image(t_main *g, double distance)
{
	if (distance < 0.2)
		return (&(g->gallery.enemy.enemy12));
	if (distance < 0.4)
		return (&(g->gallery.enemy.enemy11));
	if (distance < 0.6)
		return (&(g->gallery.enemy.enemy10));
	if (distance < 0.8)
		return (&(g->gallery.enemy.enemy9));
	if (distance < 1.0)
		return (&(g->gallery.enemy.enemy8));
	if (distance < 1.2)
		return (&(g->gallery.enemy.enemy7));
	if (distance < 1.4)
		return (&(g->gallery.enemy.enemy6));
	if (distance < 1.6)
		return (&(g->gallery.enemy.enemy5));
	if (distance < 1.8)
		return (&(g->gallery.enemy.enemy4));
	if (distance < 2.0)
		return (&(g->gallery.enemy.enemy3));
	if (distance < 2.2)
		return (&(g->gallery.enemy.enemy2));
	return (&(g->gallery.enemy.enemy1));
}

static void	draw_enemy_column(t_main *g, int x, t_ray *ray, t_enemy *enemy)
{
	int			height;
	double		hit_position;
	t_draw_pkg	pkg;
	t_im		*enemy_img;

	height = (int)(WIN_HEIGHT / ray->distance * 0.50);
	pkg.start = (WIN_HEIGHT / 2) - (height / 2);
	if (pkg.start < 0)
		pkg.start = pkg.start - (pkg.start * -1) / 2 / 2;
	pkg.end = (WIN_HEIGHT / 2) + (height / 2);
	if (pkg.end >= WIN_HEIGHT)
		pkg.end = WIN_HEIGHT - 1;
	hit_position = get_hit_position(ray, &enemy->segment);
	enemy_img = get_enemy_image(g, ray->distance);
	pkg.col = get_image_column(hit_position, enemy_img);
	pkg.height = height;
	pkg.image = enemy_img;
	pkg.window = &g->window;
	draw_column_alpha(&pkg, x, 0xFF0000, enemy->red_alpha);
}

static int	check_single_ray(t_main *g, t_enemy *e, t_cast_data *d, int x)
{
	t_ray	*old_ray;

	old_ray = get_ray_from_list(&g->rays, x);
	d->ray_d.x = cos(d->direction);
	d->ray_d.y = sin(d->direction);
	if (!find_intersection(d, e->segment))
	{
		d->direction += d->fov_rad / WIN_WIDTH;
		return (1);
	}
	d->ray->distance *= cos(d->direction - g->map.player.dov);
	if (d->ray->distance > old_ray->distance)
	{
		d->direction += d->fov_rad / WIN_WIDTH;
		return (1);
	}
	return (0);
}

void	render_enemy(t_main *g, t_enemy *e)
{
	t_cast_data	d;
	t_ray		ray;
	int			x;

	init_object_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		if (check_single_ray(g, e, &d, x))
			continue ;
		if (e->state == E_DYING)
		{
			e->dying_effect.win_x = x + 40;
			draw_text("+20", e->dying_effect);
			return ;
		}
		draw_enemy_column(g, x, &ray, e);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}
