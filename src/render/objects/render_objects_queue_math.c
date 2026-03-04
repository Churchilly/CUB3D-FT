/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects_math.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:27:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:28:21 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static int	do_angular_ranges_overlap(double start1, double end1, double start2,
		double end2)
{
	if (start1 <= end1 && start2 <= end2)
		return (fmax(start1, start2) <= fmin(end1, end2));
	if (start1 > end1)
		return (do_angular_ranges_overlap(start1, 2 * M_PI, start2, end2)
			|| do_angular_ranges_overlap(0, end1, start2, end2));
	if (start2 > end2)
		return (do_angular_ranges_overlap(start1, end1, start2, 2 * M_PI)
			|| do_angular_ranges_overlap(start1, end1, 0, end2));
	return (0);
}

static double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	is_segment_in_fov(t_player *p, t_segment *segment)
{
	t_angle	angle;
	t_angle	player;
	t_angle	object;
	double	fov_rad;
	double	swap;

	angle.s = normalize_angle(atan2(segment->s.y - p->pos.y, segment->s.x
				- p->pos.x));
	angle.e = normalize_angle(atan2(segment->e.y - p->pos.y, segment->e.x
				- p->pos.x));
	fov_rad = FOV * (M_PI / 180.0);
	player.s = normalize_angle(p->dov - (fov_rad / 2.0));
	player.e = normalize_angle(p->dov + (fov_rad / 2.0));
	object.s = fmin(angle.s, angle.e);
	object.e = fmax(angle.s, angle.e);
	if (object.e - object.s > M_PI)
	{
		swap = object.s;
		object.s = object.e;
		object.e = swap;
	}
	return (do_angular_ranges_overlap(player.s, player.e, object.s, object.e));
}

void	update_object_segment(t_segment *obj_seg, t_vector obj_pos,
		t_player *player, double width)
{
	t_vector	diff;
	double		distance;
	t_vector	delta;

	diff.x = player->pos.x - obj_pos.x;
	diff.y = player->pos.y - obj_pos.y;
	distance = sqrt((obj_pos.x - player->pos.x) * (obj_pos.x - player->pos.x)
			+ (obj_pos.y - player->pos.y) * (obj_pos.y - player->pos.y));
	delta.x = diff.y / distance;
	delta.y = (diff.x / distance) * -1;
	obj_seg->e = (t_vector){obj_pos.x + delta.x * (width / 2), obj_pos.y
		+ delta.y * (width / 2)};
	obj_seg->s = (t_vector){obj_pos.x - delta.x * (width / 2), obj_pos.y
		- delta.y * (width / 2)};
}
