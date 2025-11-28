/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_spellbook.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:10:39 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 19:54:14 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_SPELLBOOK_H
# define BONUS_SPELLBOOK_H

# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"

typedef struct s_main		t_main;

# define SPELL_COOLDOWN 60
# define SPELLBOOK_CHANGE_ANIM_SPEED 10.0
# define SPELLBOOK_WALK_ANIM_SPEED 0.8
# define SPELLBOOK_WALK_ANIM_MAX 8.0
# define SPELLBOOK_IDLE_ANIM_SPEED 0.05
# define SPELLBOOK_IDLE_ANIM_SIZE 100
# define SPELLBOOK_IDLE_START_DELAY 300
# define SPELLBOOK_WIDTH 1248
# define SPELLBOOK_HEIGHT 832
# define SPELLBOOK_TARGET_WIDTH_RATIO 0.42  // 50% of window width

typedef enum e_spell		t_spell;
typedef struct s_spellbook	t_spellbook;

enum	e_spell
{
	SPELL_FIREBALL = 0,
	SPELL_LOCK,
	SPELL_UNLOCK
};

struct s_spellbook
{
	t_spell			current;
	t_texture		*cur_texture;
	t_vector		win_pos;
	t_vector		original_win_pos;
	t_texture		texture_fireball;
	t_texture		texture_lock;
	t_texture		texture_unlock;
	int				cooldown;
	int				changing_direction;
	float			scale;
};

void	cub_spellbook(t_spellbook *spellbook, void *mlx);
void	next_spell(t_main *g);
void	prev_spell(t_main *g);
void	cast_spell(t_main *g);
void	cast_lock(t_main *g);
void	cast_unlock(t_main *g);
void	cast_fireball(t_main *g);
void	animate_spellbook(t_main *g);
void	change_animation(t_spellbook *book, int *phase, t_main *g);
void	reset_walk_animation_horizontal(t_main *g);
void	reset_walk_animation_vertical(t_main *g);
void	walk_animation(t_main *g);

#endif