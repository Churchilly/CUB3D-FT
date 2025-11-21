/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy_attack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 05:06:26 by root              #+#    #+#             */
/*   Updated: 2025/11/21 06:40:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void enemy_attack(t_enemy *enemy, t_main *g)
{
	long long curr_time;

	curr_time = current_time_ms();

	if (enemy->state == ATTACKING && curr_time - enemy->attack_time_log > 500)
		enemy->state = ALIVE;

	if (enemy->state != ATTACKING && curr_time - enemy->attack_time_log > 1000)
	{
		g->map.player.health -= ENEMY_DAMAGE;
		if (g->map.player.health < 0)
			g->map.player.health = 0;
		enemy->state = ATTACKING;
		enemy->attack_time_log = curr_time;
	}
}