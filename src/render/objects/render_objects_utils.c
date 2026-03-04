/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:50:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:53:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

t_ray	*get_ray_from_list(t_ray_list *list, int x)
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

double	get_hit_position(t_ray *ray, t_segment *seg)
{
	t_vector	distance;
	double		hit_distance;
	double		seg_len;
	double		hit_position;

	distance.x = ray->hit.x - seg->s.x;
	distance.y = ray->hit.y - seg->s.y;
	hit_distance = sqrt(distance.x * distance.x + distance.y * distance.y);
	seg_len = sqrt((seg->e.x - seg->s.x) * (seg->e.x - seg->s.x) + (seg->e.y
				- seg->s.y) * (seg->e.y - seg->s.y));
	hit_position = hit_distance / seg_len;
	return (hit_position);
}

int	get_image_column(double hit_position, t_im *image)
{
	int	image_x;

	image_x = (int)(hit_position * image->width);
	if (image_x >= image->width)
		image_x = image->width - 1;
	return (image_x);
}

void	init_object_cast_data(t_cast_data *d, t_main *g, t_ray *ray)
{
	d->fov_rad = FOV * (M_PI) / 180.0;
	d->direction = g->map.player.dov - (d->fov_rad / 2.0);
	d->player = &g->map.player;
	d->ray = ray;
}
