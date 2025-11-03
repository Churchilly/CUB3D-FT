/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 19:41:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// add animate fireball here [BURAK]

static int	interpolate_color(int color1, int color2, double t)
{
	int	c1[3];
	int	c2[3];
	int	result;

	c1[0] = (color1 >> 16) & 0xFF;
	c1[1] = (color1 >> 8) & 0xFF;
	c1[2] = color1 & 0xFF;
	c2[0] = (color2 >> 16) & 0xFF;
	c2[1] = (color2 >> 8) & 0xFF;
	c2[2] = color2 & 0xFF;
	result = ((int)(c1[0] + (c2[0] - c1[0]) * t) << 16);
	result |= ((int)(c1[1] + (c2[1] - c1[1]) * t) << 8);
	result |= (int)(c1[2] + (c2[2] - c1[2]) * t);
	return (result);
}

static void	animate_door(t_door *door)
{
	double	progress;

	if (door->state == LOCKING)
	{
		door->alpha += DOOR_LOCK_ANIMATION_SPEED;
		progress = (door->alpha - DOOR_ALPHA_OPEN) / (DOOR_ALPHA_LOCKED - DOOR_ALPHA_OPEN);
		door->color = interpolate_color(DOOR_COLOR_OPEN, DOOR_COLOR_LOCKED, progress);
		if (door->alpha >= DOOR_ALPHA_LOCKED)
		{
			door->alpha = DOOR_ALPHA_LOCKED;
			door->color = DOOR_COLOR_LOCKED;
			door->state = CLOSE;
		}
	}
	else if (door->state == UNLOCKING)
	{
		door->alpha -= DOOR_LOCK_ANIMATION_SPEED;
		progress = (DOOR_ALPHA_LOCKED - door->alpha) / (DOOR_ALPHA_LOCKED - DOOR_ALPHA_OPEN);
		door->color = interpolate_color(DOOR_COLOR_LOCKED, DOOR_COLOR_OPEN, progress);
		if (door->alpha <= DOOR_ALPHA_OPEN)
		{
			door->alpha = DOOR_ALPHA_OPEN;
			door->color = DOOR_COLOR_OPEN;
			door->state = OPEN;
		}
	}
}

void	animate_objects(t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;

	curr = g->objects.all;
	while (curr)
	{
		if (curr->type == DOOR)
			animate_door(curr->object);
		// else type == FIREBALL
		curr = curr->next;
	}
}