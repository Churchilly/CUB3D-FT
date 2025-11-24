/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 06:00:15 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	animate_objects(t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;

	curr = g->objects.all;
	while (curr)
	{
		if (curr->type == DOOR)
			animate_door(curr->object);
		else if (curr->type == ENEMY)
			animate_enemy(curr->object, g);
		else if (curr->type == FIREBALL)
			animate_fireball(curr->object, g, &g->gallery);
		else if (curr->type == ORB)
			animate_orb(curr->object, g);
		curr = curr->next;
	}
	animate_particles(g);
}
