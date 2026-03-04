/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_door.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:24:02 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:53:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static int	get_pixel_color(t_window *win, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static int	blend_colors(int bg_color, int fg_color, double alpha)
{
	int	bg_rgb[3];
	int	fg_rgb[3];
	int	rgb[3];

	bg_rgb[0] = (bg_color >> 16) & 0xFF;
	bg_rgb[1] = (bg_color >> 8) & 0xFF;
	bg_rgb[2] = bg_color & 0xFF;
	fg_rgb[0] = (fg_color >> 16) & 0xFF;
	fg_rgb[1] = (fg_color >> 8) & 0xFF;
	fg_rgb[2] = fg_color & 0xFF;
	rgb[0] = (int)(fg_rgb[0] * alpha + bg_rgb[0] * (1.0 - alpha));
	rgb[1] = (int)(fg_rgb[1] * alpha + bg_rgb[1] * (1.0 - alpha));
	rgb[2] = (int)(fg_rgb[2] * alpha + bg_rgb[2] * (1.0 - alpha));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static void	draw_door_column(t_main *g, int x, t_ray *ray, t_door *door)
{
	int	height;
	int	start;
	int	end;
	int	y;
	int	bg_color;

	height = (int)(WIN_HEIGHT / ray->distance);
	start = (-height / 2) + (WIN_HEIGHT / 2);
	if (start < 0)
		start = 0;
	end = (height / 2) + (WIN_HEIGHT / 2);
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	y = start - 1;
	while (++y <= end)
	{
		bg_color = get_pixel_color(&g->window, x, y);
		put_pixel(x, y, blend_colors(bg_color, door->color, door->alpha),
			&g->window);
	}
}

void	render_door(t_main *g, t_door *door)
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
		if (!find_intersection(&d, door->barrier))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);
		if (d.ray->distance <= old_ray->distance)
			draw_door_column(g, x, &ray, door);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}
