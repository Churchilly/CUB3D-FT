/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 16:44:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// add animate fireball here [BURAK]

static void	animate_door(t_door *door)
{
	if (door->state == OPENING)
	{
		door->alpha -= DOOR_ANIMATION_SPEED;
		if (door->alpha <= 0.0)
		{
			door->alpha = 0.0;
			door->state = OPEN;
		}
	}
	else if (door->state == CLOSING)
	{
		door->alpha += DOOR_ANIMATION_SPEED;
		if (door->alpha >= DOOR_ALPHA_MAX)
		{
			door->alpha = DOOR_ALPHA_MAX;
			door->state = CLOSE;
		}
	}
}

void	animate_objects(t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;

	while (curr)
	{
		if (curr->type == DOOR)
			animate_door(curr->object);
		// else type == FIREBALL
		curr = curr->next;
	}
}