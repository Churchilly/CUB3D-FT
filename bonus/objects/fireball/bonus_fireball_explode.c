/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fireball_explode.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:16:37 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 10:34:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void damage_nearby_enemies(t_main *g, t_vector *f_pos)
{
	t_obj_node	*obj;
	t_enemy		*enemy;

	obj = g->objects.o_static;
	while (obj)
	{
		if (obj->type == ENEMY)
		{
			enemy = (t_enemy *)obj->object;
			if (enemy->state == ALIVE || enemy->state == ATTACKING)
			{
				if (enemy->position.x >= f_pos->x - 1 && enemy->position.x <= f_pos->x + 1
					&& enemy->position.y >= f_pos->y - 1 && enemy->position.y <= f_pos->y + 1)
					damage_enemy(enemy, 40, g); // FIREBALL_DAMAGE * (inv->damage->increaser * 10)
			}
		}
		obj = obj->next;
	}
}

void fireball_explode(t_main *g, t_vector *f_pos)
{
	t_player	*player;

	player = &g->map.player;
	if (player->pos.x >= f_pos->x - 0.7 && player->pos.x <= f_pos->x + 0.7
		&& player->pos.y >= f_pos->y - 0.7 && player->pos.y <= f_pos->y + 0.7)
	{
		damage_player(g, 1);
	}
	damage_nearby_enemies(g, f_pos);
}
