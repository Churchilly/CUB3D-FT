/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy_spawn.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:37:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:38:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static int	try_spawn(t_enemy *enemy, t_map *map, t_vector_int pos)
{
	t_vector	dist;
	double		distance;

	if (pos.y < 0 || !map->matrix[pos.y] || pos.x < 0
		|| !map->matrix[pos.y][pos.x] || map->matrix[pos.y][pos.x] == '1'
		|| map->matrix[pos.y][pos.x] == 'D')
		return (0);
	dist.x = map->player.pos.x - (double)pos.x;
	dist.y = map->player.pos.y - (double)pos.y;
	distance = sqrt(dist.x * dist.x + dist.y * dist.y);
	if (distance < ENEMY_SPAWN_DIST)
		return (0);
	enemy->position.x = (double)pos.x + 0.5;
	enemy->position.y = (double)pos.y + 0.5;
	enemy->state = E_ALIVE;
	enemy->health = ENEMY_HEALTH;
	return (1);
}

void	spawn_enemy(t_enemy *enemy, t_map *map)
{
	t_vector_int	pos;
	t_vector_int	map_borders;
	int				attempts;

	map_borders.y = 0;
	while (map->matrix[map_borders.y])
		map_borders.y++;
	if (map_borders.y == 0)
		return ;
	attempts = -1;
	while (++attempts < ENEMY_SPAWN_PRECISION)
	{
		pos.y = rand() % map_borders.y;
		map_borders.x = strlen(map->matrix[pos.y]);
		if (map_borders.x <= 2)
			continue ;
		pos.x = rand() % map_borders.x;
		if (try_spawn(enemy, map, pos))
			return ;
	}
}
