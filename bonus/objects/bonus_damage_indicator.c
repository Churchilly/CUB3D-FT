/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_damage_indicator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 05:06:26 by root              #+#    #+#             */
/*   Updated: 2025/11/24 00:40:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

static double get_enemy_angle_relative_to_player(t_enemy *enemy, t_player *player)
{
	t_vector	dir;
	double		angle_to_enemy;
	double		relative_angle;

	dir.x = enemy->position.x - player->pos.x;
	dir.y = enemy->position.y - player->pos.y;

	angle_to_enemy = atan2(dir.y, dir.x);

	relative_angle = angle_to_enemy - player->dov;

	while (relative_angle < 0)
		relative_angle += 2 * M_PI;
	while (relative_angle >= 2 * M_PI)
		relative_angle -= 2 * M_PI;

	return (relative_angle * 180.0 / M_PI);
}

static void draw_arrow_pixel(t_vector_int pos, int color, double alpha, int thickness, t_window *win)
{
	int	offset_x;
	int	offset_y;
	int	blended_color;
	int half_thick;

	half_thick = thickness / 2;
	offset_y = -half_thick;
	while (offset_y <= half_thick)
	{
		offset_x = -half_thick;
		while (offset_x <= half_thick)
		{
			if (pos.x + offset_x >= 0 && pos.x + offset_x < WIN_WIDTH &&
				pos.y + offset_y >= 0 && pos.y + offset_y < WIN_HEIGHT)
			{
				blended_color = blend_alpha(color, 0x000000, alpha);
				put_pixel(pos.x + offset_x, pos.y + offset_y, blended_color, win);
			}
			offset_x++;
		}
		offset_y++;
	}
}

static void draw_arrow_segment(t_vector_int center, double angle_rad, int i, t_window *win)
{
	t_vector_int	pixel;
	double			progress;
	double			alpha;
	int				color;
	int				thickness;

	pixel.x = center.x + (int)(cos(angle_rad) * i);
	pixel.y = center.y + (int)(sin(angle_rad) * i);
	progress = (double)(i - ENEMY_EFFECT_START_OFFSET)
		/ (ENEMY_EFFECT_RADIUS - ENEMY_EFFECT_START_OFFSET);
	alpha = (1.0 - progress) * 0.7;
	thickness = (int)(8 * (1.0 - progress)) + 1;

	if (progress < 0.33)
		color = 0x00FF00;
	else if (progress < 0.66)
		color = 0xFFFF00;
	else
		color = 0xFF0000;
	draw_arrow_pixel(pixel, color, alpha, thickness, win);
}

static void draw_line_from_center(double angle_degrees, t_window *win)
{
	t_vector_int	center;
	double			angle_rad;
	int				i;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	angle_rad = (angle_degrees - 90.0) * M_PI / 180.0;
	i = ENEMY_EFFECT_START_OFFSET;
	while (i <= ENEMY_EFFECT_RADIUS)
	{
		draw_arrow_segment(center, angle_rad, i, win);
		i += 2;
	}
}

void draw_enemy_effect(t_enemy *enemy, t_player *player, t_window *win)
{
	double angle;

	if (enemy->state == ATTACKING)
	{
		angle = get_enemy_angle_relative_to_player(enemy, player);
		draw_line_from_center(angle, win);
	}
}
