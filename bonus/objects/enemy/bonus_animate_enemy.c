/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_enemy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:01:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 07:17:08 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void animate_enemy_effect(t_enemy *enemy, t_main *g)
{
	enemy->red_alpha = enemy->red_alpha - 0.1;
	if (enemy->red_alpha < 0)
		enemy->red_alpha = 0;
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
		enemy_walk(enemy, g);
		draw_enemy_effect(enemy, &g->map.player, &g->window);
	}
}
