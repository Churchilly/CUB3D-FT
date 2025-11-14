/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:12:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/14 20:33:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p

#include "../main/main.h"
#include <math.h>
#include <stdio.h>

// retrieves a ray from the packed ray list structure by screen column
static t_ray	*get_ray_from_list(t_ray_list *list, int x)
{
	t_ray_node	*curr_node;

	curr_node = list->head;
	while (curr_node)
	{
		if (x < list->package_size)
			return (&curr_node->ray_pack[x]);
		x -= list->package_size;
		curr_node = curr_node->next;
	}
	return (NULL);
}

static int	get_pixel_color(t_window *win, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
// takes two pixel color and blend them according to alpha (transparency)
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

// note to my self
// think about remove the fucking t_cast_data XD you know why
// 
static void draw_door_column(t_main *g, int x, t_ray *ray, t_door *door)
{
	int		height;
	int		start;
	int		end;
	int		y;
	int		bg_color;

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
		put_pixel(x, y, blend_colors(bg_color, door->color, door->alpha), &g->window);
	}
}

static void draw_fireball_column(t_main *g, int x, t_ray *ray, t_fireball *fireball)
{
    int height, start, end, y;
    int texture_x;
    double dx, dy, seg_len, hit_distance, hit_position;

	// positioning
    height = (int)(WIN_HEIGHT / ray->distance * 0.35); // define 0.35 as FIREBALL_SCALE
    start = (WIN_HEIGHT / 2) - (height / 2); 
    if (start < 0)
        start = start - (start * -1) / 2 / 2;
    end = (WIN_HEIGHT / 2) + (height / 2);
    if (end >= WIN_HEIGHT)
        end = WIN_HEIGHT - 1;

    // distance between hit_pos and seg
    dx = ray->hit.x - fireball->segment.s.x;
    dy = ray->hit.y - fireball->segment.s.y;
    hit_distance = sqrt(dx * dx + dy * dy);

	// segment length
    seg_len = sqrt(
        (fireball->segment.e.x - fireball->segment.s.x) *
        (fireball->segment.e.x - fireball->segment.s.x) +
        (fireball->segment.e.y - fireball->segment.s.y) *
        (fireball->segment.e.y - fireball->segment.s.y)
    );

	// final hit pos
    hit_position = hit_distance / seg_len;

    // texture column
    texture_x = (int)(hit_position * g->gallery.fireball.width);
    if (texture_x >= g->gallery.fireball.width)
        texture_x = g->gallery.fireball.width - 1;

    // draw column
    double texture_step = (double)g->gallery.fireball.height / (double)height;
    double texture_pos = 0;

    y = start - 1;
    while (++y <= end)
    {
        int texture_y = (int)texture_pos;
        if (texture_y >= g->gallery.fireball.height)
            texture_y = g->gallery.fireball.height - 1;
			
        int color = g->gallery.fireball.image[texture_y * g->gallery.fireball.width + texture_x];

        if ((unsigned int)color != 0xffffffff)
        {
            color = (color >> 8) & 0x00FFFFFF;
            put_pixel(x, y, color, &g->window);
        }
        texture_pos += texture_step;
    }
}

static void	init_cast_data(t_cast_data *d, t_main *g, t_ray *ray)
{
	d->fov_rad = FOV * (M_PI) / 180.0;
	d->direction = g->map.player.dov - (d->fov_rad / 2.0);
	d->player = &g->map.player;
	d->ray = ray;
}
// todo: fucking delete the barrier 2 if you really want it add it as a seperate obj 
// but my suggestion dont fucking lost time on it xd
static void	render_door(t_main *g, t_door *door)
{
	t_cast_data	d;
	t_ray		ray;
	int			x;
	
	init_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		t_ray	*old_ray = get_ray_from_list(&g->rays, x);
		d.ray_d.x = cos(d.direction);
		d.ray_d.y = sin(d.direction);
		if (!find_intersection(&d, door->barrier))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);// dont change need to apply this fuck here
		if (d.ray->distance > old_ray->distance)
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		draw_door_column(g, x, &ray, door);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}

static void render_fireball(t_main *g, t_fireball *f)
{
	t_cast_data d;
	t_ray ray;
	int x;
	
	init_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		t_ray	*old_ray = get_ray_from_list(&g->rays, x);
		d.ray_d.x = cos(d.direction);
		d.ray_d.y = sin(d.direction);
		if (!find_intersection(&d, f->segment))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);
		if (d.ray->distance > old_ray->distance)
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		
		draw_fireball_column(g, x, &ray, f);

		d.direction += d.fov_rad / WIN_WIDTH;
	}
}

void	render_objects(t_main *g)
{
	t_obj_node	*curr;

	clear_render_queue(&g->objects);
	create_render_queue(g);
	curr = g->objects.to_render;
	while (curr)
	{
		if (curr->type == DOOR)
			render_door(g, curr->object);
		else if (curr->type == FIREBALL)
			render_fireball(g, curr->object);
		// add fireball [BURAK]
		curr = curr->next_render;
	}
}
