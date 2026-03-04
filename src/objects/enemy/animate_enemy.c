/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_enemy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:01:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:18:27 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	animate_enemy_effect(t_enemy *enemy)
{
	enemy->red_alpha = enemy->red_alpha - 0.1;
	if (enemy->red_alpha < 0)
		enemy->red_alpha = 0;
}

void	animate_dying_enemy(t_enemy *enemy)
{
	if (enemy->state == E_DYING)
	{
		enemy->dying_effect.win_y++;
		enemy->effect_phase++;
		if (enemy->effect_phase == 50)
		{
			enemy->state = E_IDLE;
			enemy->dying_effect.win_y = WIN_HEIGHT / 2;
			enemy->position = (t_vector){-1, -1};
		}
	}
}

void	animate_enemy(t_enemy *enemy, t_main *g)
{
	static int	spawn_timer = ENEMY_SPAWN_DELAY / 2;
	int			spawn;

	if (enemy->state == E_IDLE)
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
	else if (enemy->state == E_DYING)
		animate_dying_enemy(enemy);
	else
	{
		enemy_walk(enemy, g);
		draw_enemy_effect(enemy, &g->map.player, &g->window);
	}
}
