/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy_attack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 05:06:26 by root              #+#    #+#             */
/*   Updated: 2025/11/28 22:14:58 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void enemy_attack(t_enemy *enemy, t_main *g)
{
	long long curr_time;

	curr_time = current_time_ms();

	if (enemy->state == E_ATTACKING && curr_time - enemy->attack_time_log > 500)
		enemy->state = E_ALIVE;
	if (enemy->state != E_ATTACKING && curr_time - enemy->attack_time_log > 1000)
	{
		damage_player(g, ENEMY_DAMAGE);
		enemy->state = E_ATTACKING;
		enemy->attack_time_log = curr_time;
	}
}