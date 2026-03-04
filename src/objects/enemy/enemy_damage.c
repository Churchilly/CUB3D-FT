/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:55:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:39:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	kill_enemy(t_enemy *enemy, t_main *g)
{
	enemy->health = 0;
	enemy->state = E_DYING;
	g->map.player.inventory.currency += 20;
	g->record.kill_count++;
	g->record.total_income += 20;
	enemy->effect_phase = 1;
}

void	damage_enemy(t_enemy *enemy, double damage, t_main *g)
{
	enemy->red_alpha = 0.5;
	if (damage >= enemy->health)
		kill_enemy(enemy, g);
	else
	{
		enemy->health -= damage;
	}
}
