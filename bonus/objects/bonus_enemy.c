/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:55:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/12 21:07:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// spawn enemy idea
// check the state of the enemy objects if there is an idle one if not return:
// select a random number between 0-100 
// if number > spawn_rate select a random position on map and teleport the enemy to this location (must not to close to player(1 block at least) && not inside of the wall)
// change its state to alive
static int	try_spawn(t_enemy *enemy, t_map *map, t_vector_int pos)
{
	t_vector	dist;
	double	distance;

	if (pos.y < 0 || !map->matrix[pos.y] || pos.x < 0 || !map->matrix[pos.y][pos.x]
		|| map->matrix[pos.y][pos.x] == '1' || map->matrix[pos.y][pos.x] == 'D')
		return (0);
	dist.x = map->player.pos.x - (double)pos.x;
	dist.y = map->player.pos.y - (double)pos.y;
	distance = sqrt(dist.x * dist.x + dist.y * dist.y);
	if (distance < ENEMY_SPAWN_DIST)
		return (0);
	enemy->position.x = (double)pos.x + 0.5;
	enemy->position.y = (double)pos.y + 0.5;
	enemy->state = ALIVE;
	enemy->health = ENEMY_HEALTH;
	printf("an enemy spawned at x:%fy:%f\n", enemy->position.x, enemy->position.y);
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

	new_pos.x = enemy->position.x + (direction.x * ENEMY_MOVE_SPEED * ENEMY_MOVE_MULT);
	new_pos.y = enemy->position.y + (direction.y * ENEMY_MOVE_SPEED * ENEMY_MOVE_MULT);
	map_pos.x = (int)new_pos.x;
	map_pos.y = (int)new_pos.y;
	if (map_pos.y < 0 || !map->matrix[map_pos.y]
		|| map_pos.x < 0 || !map->matrix[map_pos.y][map_pos.x]
		|| map->matrix[map_pos.y][map_pos.x] == '1'
		|| map->matrix[map_pos.y][map_pos.x] == 'D')
		return (0);
	enemy->position = new_pos;
	return (1);
}


// walk to player idea
// get current loc of the player
// change pos of enemy (towards to player) 
// if no wall on the way ofc.
// if there is a wall. change move vector 90 degrees and try again. try 3 times for check all angles (M_PI)
void	enemy_walk(t_enemy *enemy, t_map *map)
{
	t_vector	direction;
	double		distance;
	int			attempt;

	direction.x = map->player.pos.x - enemy->position.x;
	direction.y = map->player.pos.y - enemy->position.y;
	distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance < 0.001)
		return ;
	direction.x /= distance;
	direction.y /= distance;
	attempt = -1;
	while (++attempt < 6)
	{
		if (try_move(enemy, map, direction))
			return ;
		if (attempt % 2)
			direction = rotate_vector(direction, M_PI / 3);
		else
			direction = rotate_vector(direction, -(M_PI / 3));
	}
}

// check health idea
// burning state -> -1 health
// get a timer for burning state take FIREBALL_BURN times damage
// if not died change state alive
// if died change state idle loc x=-1 y=-1
void	enemy_health(t_enemy *enemy)
{
	static int	burn_timer = 60;
	static int	burn_count = 5;

	if (enemy->state == BURNING)
	{
		burn_timer -= 1;
		if (burn_timer <= 0)
		{
			enemy->health -= FIREBALL_BURN_DAMAGE;
			burn_timer = 60;
			burn_count -= 1;
			if (burn_count <= 0)
			{
				burn_count = 5;
				enemy->state = ALIVE;
			}
		}
	}
	if (enemy->health < 0)
	{
		enemy->state = DYING;
		enemy->position.x = -1;
		enemy->position.y = -1;
	}
}
