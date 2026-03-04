/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:10:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:15:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>

static t_vector	get_movement(t_main *g, t_player *player)
{
	t_vector	movement;

	movement = (t_vector){0.0, 0.0};
	if (g->key_list.w)
	{
		movement.x += P_MOVEMULT * cos(player->dov) * P_MOVESPEED;
		movement.y += P_MOVEMULT * sin(player->dov) * P_MOVESPEED;
	}
	if (g->key_list.s)
	{
		movement.x += -P_MOVEMULT * cos(player->dov) * P_MOVESPEED;
		movement.y += -P_MOVEMULT * sin(player->dov) * P_MOVESPEED;
	}
	if (g->key_list.d)
	{
		movement.x += P_MOVEMULT * cos(player->dov + (M_PI / 2)) * P_MOVESPEED;
		movement.y += P_MOVEMULT * sin(player->dov + (M_PI / 2)) * P_MOVESPEED;
	}
	if (g->key_list.a)
	{
		movement.x += P_MOVEMULT * cos(player->dov - (M_PI / 2)) * P_MOVESPEED;
		movement.y += P_MOVEMULT * sin(player->dov - (M_PI / 2)) * P_MOVESPEED;
	}
	movement = check_collision(g, movement);
	return (movement);
}

void	play_footstep(int moved)
{
	static int		step = 0;
	static double	last_time = 0;
	double			curr_time;

	curr_time = current_time_ms();
	if (moved && curr_time - last_time > 240)
	{
		if (step == 0)
			system(AUDIO_FOOTSTEP_1);
		else if (step == 1)
			system(AUDIO_FOOTSTEP_2);
		else if (step == 2)
			system(AUDIO_FOOTSTEP_3);
		step = (step + 1) % 3;
		last_time = curr_time;
	}
}

void	change_position(t_main *g)
{
	t_player	*player;
	t_vector	movement;

	player = &g->map.player;
	movement = (t_vector){0.0, 0.0};
	movement = get_movement(g, player);
	player->pos.x += movement.x;
	player->pos.y += movement.y;
	play_footstep(fabs(movement.x) > 0.0 || fabs(movement.y) > 0.0);
	raycasting(g);
}

void	change_direction(t_main *g)
{
	t_player	*player;
	double		rotation_step;

	player = &g->map.player;
	rotation_step = (FOV * M_PI / 180.0) * SENSITIVITY * 0.05;
	if (g->key_list.arrow_r)
	{
		player->dov += rotation_step;
		if (player->dov >= (M_PI * 2))
			player->dov -= (M_PI * 2);
		list_pop_left(&g->rays);
		raycasting_right_rotation(g);
	}
	if (g->key_list.arrow_l)
	{
		player->dov -= rotation_step;
		if (player->dov < 0)
			player->dov += (2 * M_PI);
		list_pop_right(&g->rays);
		raycasting_left_rotation(g);
	}
}

void	change_direction_advanced(t_main *g, int direction, int weight)
{
	t_player	*player;
	double		rotation_step;

	player = &g->map.player;
	if (weight < 0)
		weight = -weight;
	rotation_step = (((FOV * M_PI / 180.0) * SENSITIVITY) + weight * 0.025)
		* 0.05;
	if (direction == 'R')
	{
		player->dov += rotation_step;
		if (player->dov >= (M_PI * 2))
			player->dov -= (M_PI * 2);
		list_pop_left(&g->rays);
		raycasting_right_rotation(g);
	}
	if (direction == 'L')
	{
		player->dov -= rotation_step;
		if (player->dov < 0)
			player->dov += (2 * M_PI);
		list_pop_right(&g->rays);
		raycasting_left_rotation(g);
	}
}
