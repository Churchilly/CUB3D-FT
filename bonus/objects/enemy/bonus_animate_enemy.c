/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_enemy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:01:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 05:56:19 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../main/main.h"

static void animate_enemy_effect(t_enemy *enemy, t_main *g)
{
	static long long time_log = 0;
	long long curr_time;
	
	curr_time = current_time_ms();
	if (curr_time - time_log > 50)
	{
		enemy->red_alpha = enemy->red_alpha - 0.1;
		if (enemy->red_alpha < 0)
			enemy->red_alpha = 0;
		time_log = curr_time;
	}
}

void animate_enemy(t_enemy *enemy, t_main *g)
{
	static int	spawn_timer = ENEMY_SPAWN_DELAY / 2;
	int			spawn;

	if (enemy->state == IDLE)
	{
		spawn_timer++;
		if (spawn_timer >= ENEMY_SPAWN_DELAY)
		{
			spawn = rand() % 100;
			if (spawn < ENEMY_SPAWN_RATE)
				spawn_enemy(enemy, &g->map);
			spawn_timer = 0;
		}
	}
	else
	{
		animate_enemy_effect(enemy, g);
		enemy_walk(enemy, g);
		draw_enemy_effect(enemy, &g->map.player, &g->window);
	}
}
