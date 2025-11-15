/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:22 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/15 23:40:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// add animate fireball here [BURAK]

static int	interpolate_color(int color1, int color2, double t)
{
	int	c1[3];
	int	c2[3];
	int	result;

	c1[0] = (color1 >> 16) & 0xFF;
	c1[1] = (color1 >> 8) & 0xFF;
	c1[2] = color1 & 0xFF;
	c2[0] = (color2 >> 16) & 0xFF;
	c2[1] = (color2 >> 8) & 0xFF;
	c2[2] = color2 & 0xFF;
	result = ((int)(c1[0] + (c2[0] - c1[0]) * t) << 16);
	result |= ((int)(c1[1] + (c2[1] - c1[1]) * t) << 8);
	result |= (int)(c1[2] + (c2[2] - c1[2]) * t);
	return (result);
}

static void	animate_door(t_door *door)
{
	double	progress;

	if (door->state == LOCKING)
	{
		door->alpha += DOOR_LOCK_ANIMATION_SPEED;
		progress = (door->alpha - DOOR_ALPHA_OPEN) / (DOOR_ALPHA_LOCKED - DOOR_ALPHA_OPEN);
		door->color = interpolate_color(DOOR_COLOR_OPEN, DOOR_COLOR_LOCKED, progress);
		if (door->alpha >= DOOR_ALPHA_LOCKED)
		{
			door->alpha = DOOR_ALPHA_LOCKED;
			door->color = DOOR_COLOR_LOCKED;
			door->state = CLOSE;
		}
	}
	else if (door->state == UNLOCKING)
	{
		door->alpha -= DOOR_LOCK_ANIMATION_SPEED;
		progress = (DOOR_ALPHA_LOCKED - door->alpha) / (DOOR_ALPHA_LOCKED - DOOR_ALPHA_OPEN);
		door->color = interpolate_color(DOOR_COLOR_LOCKED, DOOR_COLOR_OPEN, progress);
		if (door->alpha <= DOOR_ALPHA_OPEN)
		{
			door->alpha = DOOR_ALPHA_OPEN;
			door->color = DOOR_COLOR_OPEN;
			door->state = OPEN;
		}
	}
}

static void animate_enemy(t_enemy *enemy, t_map *map)
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
				spawn_enemy(enemy, map);
			spawn_timer = 0;
		}
	}
	else
	{
		enemy_walk(enemy, map);
		enemy_health(enemy);
		// add collision check here [BURAK]
	}
}

// [BURAK]
static void	animate_fireball(t_fireball *f, t_main *g, t_cub3_gallery *gal)
{
	static long long time_log = 0;
	static long long time_log_2 = 0;
	long long curr_time;
	t_im swap;

	curr_time = current_time_ms();
	if (curr_time - time_log > 120)
	{
		swap = gal->fireball;
		gal->fireball = gal->fireball2;
		gal->fireball2 = gal->fireball3;
		gal->fireball3 = gal->fireball4;
		gal->fireball4 = swap;
		
		time_log = curr_time;
	}
	if (f->state == FLY && curr_time - time_log_2 > 5)
	{
		f->position.x += cos(f->direction) * 0.05;
		f->position.y += sin(f->direction) * 0.05;
		
		if (g->map.matrix[(int)f->position.y][(int)f->position.x] == '1')
		{
			f->state = IDLE;
			f->position = (t_vector){-1, -1};
			printf("BOOOOOOOOOOOOOMMMM\n");
		}

		time_log_2 = curr_time;
	}

}


void	animate_objects(t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;

	curr = g->objects.all;
	while (curr)
	{
		if (curr->type == DOOR)
			animate_door(curr->object);
		else if (curr->type == ENEMY)
			animate_enemy(curr->object, &g->map);
		else if (curr->type == FIREBALL)
			animate_fireball(curr->object, g, &g->gallery);
		curr = curr->next;
	}
}