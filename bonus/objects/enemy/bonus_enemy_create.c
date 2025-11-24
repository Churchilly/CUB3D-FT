/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:23:30 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 10:25:22 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	create_enemies(t_main *g)
{
	int	i;
	t_enemy *enemy;

	i = -1;
	while (++i < NUM_OF_ENEMIES)
	{
		enemy = alloc(sizeof(t_enemy), STATIC);
		enemy->health = ENEMY_HEALTH;
		enemy->state = IDLE;
		enemy->position.x = -1.0;
		enemy->position.y = -1.0;
		enemy->red_alpha = 0.0;
		enemy->attack_time_log = 0;
		add_object(&g->objects, ENEMY, enemy, STATIC);
	}
}
