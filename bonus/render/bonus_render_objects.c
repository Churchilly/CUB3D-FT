/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:12:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 02:43:49 by btuncer          ###   ########.fr       */
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

double get_hit_position(t_ray *ray, t_segment *seg)
{
    t_vector distance;
    double hit_distance;
    double seg_len;
    double hit_position;

    distance.x = ray->hit.x - seg->s.x;
    distance.y = ray->hit.y - seg->s.y;
    hit_distance = sqrt(distance.x * distance.x + distance.y * distance.y);
    seg_len = sqrt((seg->e.x - seg->s.x) * (seg->e.x - seg->s.x) +
        (seg->e.y - seg->s.y) * (seg->e.y - seg->s.y));
    hit_position = hit_distance / seg_len;
    return (hit_position);
}

int get_image_column(double hit_position, t_im *image)
{
	int image_x;

	image_x = (int)(hit_position * image->width);
	if (image_x >= image->width)
		image_x = image->width - 1;
	return (image_x);
}

static void draw_fireball_column(t_main *g, int x, t_ray *ray, t_fireball *fireball)
{
    int height;
    double hit_position;
	t_draw_pkg pkg;

    height = (int)(WIN_HEIGHT / ray->distance * 0.35);
    pkg.start = (WIN_HEIGHT / 2) - (height / 2); 
    if (pkg.start < 0)
        pkg.start = pkg.start - (pkg.start * -1) / 2 / 2;
    pkg.end = (WIN_HEIGHT / 2) + (height / 2);
    if (pkg.end >= WIN_HEIGHT)
        pkg.end = WIN_HEIGHT - 1;
    hit_position = get_hit_position(ray, &fireball->segment);
    pkg.col = get_image_column(hit_position, &g->gallery.fireball);
	pkg.height = height;
	pkg.image = &g->gallery.fireball;
	draw_column(&pkg, x, &g->window);
}

static void draw_particle_column(t_main *g, int x, t_ray *ray, t_fire_particle *particle)
{
    int height;
    double hit_position;
	t_draw_pkg pkg;

    height = (int)(WIN_HEIGHT / ray->distance * 0.30);
    pkg.start = (WIN_HEIGHT / 2) - (height / 2) / 2 / 2 / 2 + particle->start_y;
    if (pkg.start < 0)
        pkg.start = pkg.start - (pkg.start * -1) / 2 / 2;
    pkg.end = (WIN_HEIGHT / 2) + (height / 2);
    if (pkg.end >= WIN_HEIGHT)
        pkg.end = WIN_HEIGHT - 1;
    hit_position = get_hit_position(ray, &particle->segment);
	pkg.col = get_image_column(hit_position, &g->gallery.fireball_particle_1);
	pkg.height = height;
	pkg.image = &particle->image;
	draw_column(&pkg, x, &g->window);
}

static t_im	*get_enemy_image(t_main *g, double distance)
{
	if (distance < 0.2)
		return (&(g->gallery.enemy12));
	if (distance < 0.4)
		return (&(g->gallery.enemy11));
	if (distance < 0.6)
		return (&(g->gallery.enemy10));
	if (distance < 0.8)
		return (&(g->gallery.enemy9));
	if (distance < 1.0)
		return (&(g->gallery.enemy8));
	if (distance < 1.2)
		return (&(g->gallery.enemy7));
	if (distance < 1.4)
		return (&(g->gallery.enemy6));
	if (distance < 1.6)
		return (&(g->gallery.enemy5));
	if (distance < 1.8)
		return (&(g->gallery.enemy4));
	if (distance < 2.0)
		return (&(g->gallery.enemy3));
	if (distance < 2.2)
		return (&(g->gallery.enemy2));
	return (&(g->gallery.enemy1));
}

static void draw_enemy_column(t_main *g, int x, t_ray *ray, t_enemy *enemy)
{
    int 		height;
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
	draw_column_alpha(&pkg, x, &g->window, 0xFF0000, enemy->red_alpha);
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
static void	render_enemy(t_main *g, t_enemy *e)
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
		if (!find_intersection(&d, e->segment))
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
		draw_enemy_column(g, x, &ray, e);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}
static void render_particle(t_main *g, t_fire_particle *particle)
{
	t_cast_data d;
	t_ray ray;
	int x;

	init_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		t_ray *old_ray = get_ray_from_list(&g->rays, x);
		d.ray_d.x = cos(d.direction);
		d.ray_d.y = sin(d.direction);
		if (!find_intersection(&d, particle->segment))
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
		draw_particle_column(g, x, &ray, particle);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}

static void draw_orb_column(t_main *g, int x, t_ray *ray, t_orb *orb)
{
    int height;
    double hit_position;
	t_draw_pkg pkg;
    int y_offset;

    height = (int)(WIN_HEIGHT / ray->distance * 0.25 * 0.5);
    y_offset = 200;
    pkg.start = (WIN_HEIGHT / 2) - (height / 2) + y_offset;
    if (pkg.start < 0)
        pkg.start = 0;
    pkg.end = (WIN_HEIGHT / 2) + (height / 2) + y_offset;
    if (pkg.end >= WIN_HEIGHT)
        pkg.end = WIN_HEIGHT - 1;
    hit_position = get_hit_position(ray, &orb->segment);
    pkg.col = get_image_column(hit_position, &g->gallery.pokeball);
	pkg.height = height;
	pkg.image = &g->gallery.pokeball;
	draw_column(&pkg, x, &g->window);
}

static void render_orb(t_main *g, t_orb *orb)
{
	t_cast_data d;
	t_ray ray;
	int x;

	init_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		t_ray *old_ray = get_ray_from_list(&g->rays, x);
		d.ray_d.x = cos(d.direction);
		d.ray_d.y = sin(d.direction);
		if (!find_intersection(&d, orb->segment))
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
		draw_orb_column(g, x, &ray, orb);
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
		else if (curr->type == PARTICLE)
			render_particle(g, curr->object);
		else if (curr->type == ENEMY)
			render_enemy(g, curr->object);
		else if (curr->type == ORB)
			render_orb(g, curr->object);
		curr = curr->next_render;
	}
}
