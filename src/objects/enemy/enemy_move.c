/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:38:28 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:40:17 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

static t_vector	rotate_vector(t_vector vec, double angle)
{
	t_vector	rotated;
	double		cos_a;
	double		sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	rotated.x = vec.x * cos_a - vec.y * sin_a;
	rotated.y = vec.x * sin_a + vec.y * cos_a;
	return (rotated);
}

static int	try_move(t_enemy *enemy, t_map *map, t_vector direction)
{
	t_vector		new_pos;
	t_vector_int	map_pos;

	new_pos.x = enemy->position.x + (direction.x * ENEMY_MOVE_SPEED
			* ENEMY_MOVE_MULT);
	new_pos.y = enemy->position.y + (direction.y * ENEMY_MOVE_SPEED
			* ENEMY_MOVE_MULT);
	map_pos.x = (int)new_pos.x;
	map_pos.y = (int)new_pos.y;
	if (map_pos.y < 0 || !map->matrix[map_pos.y] || map_pos.x < 0
		|| !map->matrix[map_pos.y][map_pos.x]
		|| map->matrix[map_pos.y][map_pos.x] == '1'
		|| map->matrix[map_pos.y][map_pos.x] == 'D')
		return (0);
	enemy->position = new_pos;
	return (1);
}

void	enemy_walk(t_enemy *enemy, t_main *g)
{
	t_vector	direction;
	double		distance;
	int			attempt;

	direction.x = g->map.player.pos.x - enemy->position.x;
	direction.y = g->map.player.pos.y - enemy->position.y;
	distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance < ENEMY_RADIUS + PLAYER_RADIUS)
	{
		enemy_attack(enemy, g);
		return ;
	}
	direction.x /= distance;
	direction.y /= distance;
	attempt = -1;
	while (++attempt < 6)
	{
		if (try_move(enemy, &g->map, direction))
			return ;
		if (attempt % 2)
			direction = rotate_vector(direction, M_PI / 3);
		else
			direction = rotate_vector(direction, -(M_PI / 3));
	}
}
