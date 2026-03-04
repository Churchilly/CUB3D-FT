/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:44:50 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/30 02:57:30 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>

void	next_spell(t_main *g)
{
	if (g->spellbook.changing_direction != 0)
		return ;
	g->spellbook.changing_direction = 1;
	g->spellbook.cooldown = SPELL_COOLDOWN;
}

void	prev_spell(t_main *g)
{
	if (g->spellbook.changing_direction != 0)
		return ;
	g->spellbook.changing_direction = -1;
	g->spellbook.cooldown = SPELL_COOLDOWN;
}

void	cast_spell(t_main *g)
{
	use_mana(g, 42.0);
	if (g->spellbook.cooldown > 0 || g->spellbook.changing_direction != 0)
		return ;
	if (g->spellbook.current == SPELL_FIREBALL)
	{
		system(AUDIO_FIREBALL);
		cast_fireball(g);
	}
	else if (g->spellbook.current == SPELL_LOCK)
		cast_lock(g);
	else if (g->spellbook.current == SPELL_UNLOCK)
		cast_unlock(g);
}

static void	_init_texture(t_texture *src, char *dst, void *mlx)
{
	src->img = mlx_xpm_file_to_image(mlx, dst, &src->width, &src->height);
	if (!src->img)
	{
		printf("Error: Failed to load texture %s\n", dst);
		exit(1);
	}
	src->addr = mlx_get_data_addr(src->img, &src->bits_per_pixel,
			&src->line_length, &src->endian);
}

void	cub_spellbook(t_spellbook *spellbook, void *mlx)
{
	int	target_width;
	int	scaled_width;
	int	scaled_height;

	_init_texture(&spellbook->texture_fireball,
		"_textures/fireball_spellbook.xpm", mlx);
	_init_texture(&spellbook->texture_lock, "_textures/lock_spellbook.xpm",
		mlx);
	_init_texture(&spellbook->texture_unlock, "_textures/unlock_spellbook.xpm",
		mlx);
	spellbook->current = SPELL_FIREBALL;
	spellbook->cur_texture = &spellbook->texture_fireball;
	spellbook->cooldown = 0;
	spellbook->changing_direction = 0;
	target_width = (int)(WIN_WIDTH * SPELLBOOK_TARGET_WIDTH_RATIO);
	spellbook->scale = (float)SPELLBOOK_WIDTH / (float)target_width;
	scaled_width = (int)(SPELLBOOK_WIDTH / spellbook->scale);
	scaled_height = (int)(SPELLBOOK_HEIGHT / spellbook->scale);
	spellbook->win_pos.x = (WIN_WIDTH - scaled_width) / 2;
	spellbook->win_pos.y = WIN_HEIGHT - scaled_height + (WIN_HEIGHT / 10);
	spellbook->original_win_pos.x = spellbook->win_pos.x;
	spellbook->original_win_pos.y = spellbook->win_pos.y;
}
