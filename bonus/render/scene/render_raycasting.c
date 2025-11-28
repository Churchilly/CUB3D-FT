/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:20:16 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:14:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>
#include <stdio.h>

static t_ray_node	*init_cast_data(t_cast_data *d, t_main *g)
{
	d->fov_rad = FOV * (M_PI) / 180.0;
	d->direction = g->map.player.dov - (d->fov_rad / 2.0);
	d->player = &g->map.player;
	d->door_walls = g->map.door_walls;
	return (g->rays.head);
}

void	raycasting(t_main *g)
{
	t_cast_data	d;
	t_ray_node	*curr;
	int			i;

	curr = init_cast_data(&d, g);
	while (curr)
	{
		i = -1;
		while (++i < g->rays.package_size)
		{
			d.ray = &(curr->ray_pack[i]);
			d.ray_d.x = cos(d.direction);
			d.ray_d.y = sin(d.direction);
			raycast_single(&d, g->map.matrix);
			curr->ray_pack[i].raw_distance = curr->ray_pack[i].distance;
			curr->ray_pack[i].distance *= cos(d.direction - g->map.player.dov);
			d.direction += d.fov_rad / WIN_WIDTH;
		}
		curr = curr->next;
	}
}

static void	cast_ray(t_main *g, t_cast_data *d, t_ray_node *curr, int idx)
{
	d->ray_d.x = cos(d->direction);
	d->ray_d.y = sin(d->direction);
	raycast_single(d, g->map.matrix);
	curr->ray_pack[idx].raw_distance = curr->ray_pack[idx].distance;
	curr->ray_pack[idx].distance *= cos(d->direction - g->map.player.dov);
}

void	raycasting_right_rotation(t_main *g)
{
	t_cast_data	d;
	t_ray_node	*curr;
	int			i;

	curr = init_cast_data(&d, g);
	while (curr)
	{
		i = -1;
		while (++i < g->rays.package_size)
		{
			d.ray = &(curr->ray_pack[i]);
			if (curr->next == NULL)
				cast_ray(g, &d, curr, i);
			else
				curr->ray_pack[i].distance = curr->ray_pack[i].raw_distance
					* cos(d.direction - g->map.player.dov);
			d.direction += d.fov_rad / WIN_WIDTH;
		}
		curr = curr->next;
	}
}

void	raycasting_left_rotation(t_main *g)
{
	t_cast_data	d;
	t_ray_node	*curr;
	int			i;

	curr = init_cast_data(&d, g);
	while (curr)
	{
		i = -1;
		while (++i < g->rays.package_size)
		{
			d.ray = &(curr->ray_pack[i]);
			if (curr->prev == NULL)
				cast_ray(g, &d, curr, i);
			else
				curr->ray_pack[i].distance = curr->ray_pack[i].raw_distance
					* cos(d.direction - g->map.player.dov);
			d.direction += d.fov_rad / WIN_WIDTH;
		}
		curr = curr->next;
	}
}
