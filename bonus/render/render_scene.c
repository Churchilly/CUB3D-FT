/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:25:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/13 19:42:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../main/main.h"
#include <math.h>

static t_texture	*get_wall_texture(t_main *g, char wall_side)
{
	if (wall_side == 'N')
		return (&g->map.texture_no);
	else if (wall_side == 'S')
		return (&g->map.texture_so);
	else if (wall_side == 'E')
		return (&g->map.texture_ea);
	else if (wall_side == 'W')
		return (&g->map.texture_we);
	return (&g->map.texture_no);
}

static void	init_render_data(t_render_data *d, t_main *g, t_ray *ray)
{
	d->wall_texture = get_wall_texture(g, ray->side);
	d->wall_height = (int)(WIN_HEIGHT / ray->distance);
	d->wall_start = (-d->wall_height / 2) + (WIN_HEIGHT / 2);
	if (d->wall_start < 0)
		d->wall_start = 0;
	d->wall_end = (d->wall_height / 2) + (WIN_HEIGHT / 2);
	if (d->wall_end >= WIN_HEIGHT)
		d->wall_end = WIN_HEIGHT - 1;
	if (ray->side == 'N' || ray->side == 'S')
		d->wall_hit = ray->hit.x;
	else
		d->wall_hit = ray->hit.y;
	d->wall_hit = d->wall_hit - floor(d->wall_hit);
} 

static void	draw_wall_column(t_main *g, int x, t_ray *ray)
{
	t_render_data	d;
	int				y;
	int				color;
	
	init_render_data(&d, g, ray);
	d.texture_x = (int)(d.wall_hit * (double)d.wall_texture->width);
	if (d.texture_x < 0)
		d.texture_x = 0;
	if (d.texture_x >= d.wall_texture->width)
		d.texture_x = d.wall_texture->width - 1;
	d.texture_step = (double)d.wall_texture->height / (double)d.wall_height;
	d.texture_pos = (d.wall_start - WIN_HEIGHT / 2 + d.wall_height / 2) * d.texture_step;
	y = d.wall_start - 1;
	while (++y <= d.wall_end)
	{
		d.texture_y = (int)d.texture_pos;
		if (d.texture_y < 0)
			d.texture_y = 0;
		if (d.texture_y >= d.wall_texture->height)
			d.texture_y = d.wall_texture->height - 1;
		d.texture_pos += d.texture_step;
		color = *(int *)(d.wall_texture->addr + (d.texture_y * d.wall_texture->line_length + d.texture_x * (d.wall_texture->bits_per_pixel / 8)));
		put_pixel(x, y, color, &g->window);
	}
}

void draw_floor_column(t_main *g, int x, t_ray *ray)
{
	int			y;
	double		row_distance;
	double		fov_rad;
	double		ray_angle;
	t_vector	ray_dir;
	t_vector	floor_pos;
	int			texture_x;
	int			texture_y;
	int			color;
	t_texture	*floor_tex;
	
	floor_tex = &g->map.texture_no;
	
	fov_rad = FOV * M_PI / 180.0;
	ray_angle = g->map.player.dov - (fov_rad / 2.0) + ((double)x / WIN_WIDTH) * fov_rad;
	ray_dir.x = cos(ray_angle);
	ray_dir.y = sin(ray_angle);
	
	y = WIN_HEIGHT / 2;
	while (++y < WIN_HEIGHT)
	{
		row_distance = (WIN_HEIGHT / 2.0) / (y - WIN_HEIGHT / 2.0);
		row_distance /= cos(ray_angle - g->map.player.dov);
		
		floor_pos.x = g->map.player.pos.x + ray_dir.x * row_distance;
		floor_pos.y = g->map.player.pos.y + ray_dir.y * row_distance;
		
		texture_x = (int)(floor_pos.x * floor_tex->width) % floor_tex->width;
		texture_y = (int)(floor_pos.y * floor_tex->height) % floor_tex->height;
		if (texture_x < 0)
			texture_x += floor_tex->width;
		if (texture_y < 0)
			texture_y += floor_tex->height;
		color = *(int *)(floor_tex->addr + 
				(texture_y * floor_tex->line_length + 
				 texture_x * (floor_tex->bits_per_pixel / 8)));
		
		put_pixel(x, y, color, &g->window);
	}
}

void	render_scene(t_main *g)
{
	t_ray_node	*current;
	int			i;
	int			j;
	
	current = g->rays.head;
	i = -1;
	while (current && ++i < g->rays.list_size)
	{
		j = -1;
		while (++j < g->rays.package_size)
		{
			draw_floor_column(g, j + (i * g->rays.package_size), &(current->ray_pack[j]));
			draw_wall_column(g, j + (i * g->rays.package_size), &(current->ray_pack[j]));
		}
		current = current->next;
	}
}
