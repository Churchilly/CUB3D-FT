/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:55:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/09 02:25:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
// spawn enemy idea
// check the state of the enemy objects if there is an idle one:
// select a random number between 0-100 
// if number > spawn_rate select a random position on map and teleport the enemy to this location (must not to close to player(1 block at least) && not inside of the wall)
// change its state to alive
void	spawn_enemy(t_main *g)
{
	
}

// walk to player idea
// get current loc of the player
// change pos of enemy (towards to player) 
// if no wall on the way ofc.
// if there is a wall just dont walk (since enemies are stupid or i dont care much XD)
void	enemy_walk()
{
	
}

// check health idea
// burning state -> -1 health
// get a timer for burning state take FIREBALL_BURN times damage
// if not died change state alive
// if died change state idle loc x=-1 y=-1
void	enemy_health()
{
	
}
